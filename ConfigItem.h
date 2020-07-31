// -*- mode: C++; c-basic-offset: 4; -*-

#ifndef _ConfigItem_h_
#define _ConfigItem_h_

/**

This header defines the ConfigSet and ConfigItem API, and a template
ConfigItemT<T> which implements a ConfigItem for a specific storage type.

By limiting this header to only the interfaces and not the implementations,
it is more concise and easier to follow.  It can also be included in lots
of places, but the source modules which include it will not need to be
recompiled if the implementations change.

The default implementations for the ConfigItemT template are in
ConfigItem_impl.h.  Code which wants to use ConfigItemT implementations for
new types need to include that header and then explicitly instantiate the
template for the desired type.  ConfigItem.cpp contains explicit
instantiations for a few basic types: bool, int, float, std::string.

 **/

#include <string>

class ConfigSet;

/**
 * ConfigItem is a virtual base class for holding config settings.  A
 * config setting has a name, and it stores a value which can be translated
 * to and from string using the setString() and getString() methods.  A
 * ConfigItem can also belong to a ConfigSet.
 **/
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


/**
 * ConfigItemT is a template which implements the ConfigItem interface and
 * stores config values as the template parameter type.
 **/
template <typename T>
class ConfigItemT : public ConfigItem
{
    public:
    ConfigItemT(ConfigSet* cs, const std::string& name, const T& value);

    virtual std::string getString();

    virtual void setString(const std::string& value);

    /**
     * Allow the ConfigItemT object to be used directly where the
     * underlying type is needed, by defining an operator which casts to a
     * const reference.  This is const so callers cannot change the stored
     * value outside the control of this class.
     **/
    inline
    operator const T&() const
    {
    	return _value;
    }

    /**
     * Using a template type for the rhs allows comparison against
     * different numeric types.  The implementation will use the built-in
     * conversions to compare with the storage type.
     **/
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

private:
    T _value;
};


/**
 * Allow ConfigItemT types to be compared against the underlying type when
 * on the right side of operator==().
 **/
template <typename T>
bool
operator==(const T& lhs, const ConfigItemT<T>& rhs);


#endif // _ConfigItem_h_
