/*
 * (C) Copyright 1996-2012 ECMWF.
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 * In applying this licence, ECMWF does not waive the privileges and immunities 
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */


#include "eclib/Context.h"
#include "eclib/Configurable.h"
#include "eclib/Resource.h"
#include "eclib/ResourceMgr.h"

ResourceBase::ResourceBase(Configurable* owner,const string& str) :
    owner_( owner ? owner : &Context::instance() ),
	inited_(false),
    converted_(false)
{
	if(owner_) owner_->add(this);	

	const char *p = str.c_str();

	while(*p)
	{
		string *s = &name_;
		char   x  = *p;
		int len   = 0;

		switch(x)
		{
			case '$': s = &environment_; break;
			case '-': s = &options_;     break;
		}

		*s = p;

		while(*p && *p != ';')
		{
			len++;
			p++;
		}

		s->resize(len);

		if(*p) p++; 

	}
}

ResourceBase::ResourceBase(const string& name, const StringDict& args):
			owner_( &Context::instance() ),
			inited_(false),
			converted_(false),
            name_(name)
{
	if(owner_) owner_->add(this);	
    
    init(&args);
}

ResourceBase::~ResourceBase()
{
	if(owner_) owner_->remove(this);
}

void ResourceBase::init(const StringDict* args)
{
	if(inited_) return;

	// First look in config file
	// First look for an option on the command line

	if(options_ != "")
	{
		for(int i = 1; i < Context::instance().argc(); i++)
			if(options_ == Context::instance().argv(i))
			{
                if( i+1 == Context::instance().argc() || Context::instance().argv(i+1)[0] == '-' )
                    valueStr_ = "true";
				else
                    valueStr_ = Context::instance().argv(i+1);
				inited_ = true;
				return;
			}
	}

	// Then look for an environment variable

	if(environment_ != "")
	{
		const char *p = ::getenv(environment_.c_str()+1);
		if(p) {
			valueStr_ = p;
			inited_ = true;
			return;
		}
	}

	// Otherwise look in the config file

	if(name_ != "")
	{
		bool found = false;
		string s;

		if(owner_)
			found = ResourceMgr::lookUp(owner_->kind(),owner_->name(),name_,args,s);
		else
			found = ResourceMgr::lookUp("","",name_,args,s);	
		
		if(found) valueStr_ = s;

	}

	// Else use default. This is done in Resource

    inited_ = true;
	converted_ = true;
}

void ResourceBase::convert()
{
    if(!converted_)
    {
        setValue(valueStr_);
        converted_ = true;
    }
}

string ResourceBase::name() const
{
	if(owner_)
		return owner_->kind() + '.' + owner_->name() + '.' + name_;
	else 
		return name_;
}

void ResourceBase::dump(ostream& s) const
{

	// need const_cast here
	((ResourceBase*)this)->init();

	s << "# " << name_ <<":" << endl;

	if(options_ != "")     s << "#   command line option  " << options_     << endl;
	if(environment_ != "") 
	{
		s << "#   environment variable " << environment_ << " ";
		const char *p = getenv(environment_.c_str()+1);
		if(p) s << "(defined as " << p << ")";
		else  s << "(undefined)";
		s << endl;
	}

	s << name() << " : " << getValue();

	s << endl;
}

#ifdef AIX
// force template instantiation
#pragma define(Resource<bool>)
#pragma define(Resource<long>)
#pragma define(Resource<string>)
#endif
