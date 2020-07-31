// -*- mode: C++; c-basic-offset: 4; -*-

#ifndef _ConfigItem_h_
#define _ConfigItem_h_

#include <string>

class ConfigSet;

class ConfigItem
{
public:
    ConfigItem(ConfigSet* cs, const std::string& name);

    virtual std::string getString() = 0;

    virtual void setString(const std::string& value) = 0;

private:
    std::string _name;
    ConfigSet* _cs;
};

class ConfigSet
{
public:
    ConfigSet();
};


template <typename T>
class ConfigItemT : public ConfigItem
{
    public:
    ConfigItemT(ConfigSet* cs, const std::string& name, const T& value);

    virtual std::string getString();

    virtual void setString(const std::string& value);

#ifdef RETURN_NON_CONST_REF
    inline
    operator const T&() const
    {
    	return _value;
    }

    inline
    operator T&()
    {
    	return _value;
    }
#endif

#ifdef RETURN_COPY
    inline
    operator T() const
    {
    	return _value;
    }
#endif
    
    inline
    operator const T&() const
    {
    	return _value;
    }

    // Using a template type for the rhs allows comparison against
    // different numeric types.  The implementation will use the built-in
    // conversions to compare with the storage type.
    template <typename V>
    inline bool
    operator==(const V& v) const
    {
        return _value == v;
    }

    ConfigItemT<T>&
    operator=(const T& v)
    {
        _value = v;
        return *this;
    }

    inline T&
    value()
    {
	return _value;
    }

    inline const T&
    value() const
    {
	return _value;
    }

private:
    T _value;
};


template <typename T>
bool
operator==(const T& lhs, const ConfigItemT<T>& rhs);


#endif // _ConfigItem_h_
