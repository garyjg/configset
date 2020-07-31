// -*- mode: C++; c-basic-offset: 4; -*-

/**

This file contains default implementations for the ConfigItemT template, as
well as some specializations for ConfigItemT<bool> and
ConfigItemT<std::string>.

These are *only* implementations, they are not definitions.  Even the
specializations are not definitions.  The compiler will not define
(instantiate) any template implementations until it needs to compile code
which uses the ConfigItemT template with a specific type parameter.  For
example, if the compiler encounters a use of type ConfigItemT<bool>, and if
it has read implementations for that type (either the default
implementations or the specializations for the bool type), then the
compiler will use those implementations to instantiate (define) the code
for the instantiated type (ConfigItemT<bool>).

If the compiler encounters a use of ConfigItemT<bool> but has not read
implementations at that point (ie, this header file has not been included
prior to the use of the template), then the compiler just generates code to
call the corresponding type definitions.  In other words, if the code
constructs a ConfigItemT<bool>, it generates a call to the
ConfigItemT<bool> constructor.  If the code calls
ConfigItemT<bool>::getString(), then the compiler generates a call to that
method, but it does not define that method.  The definition of the
constructor or the method must exist somewhere else, in some other object
module or library, otherwise the linker will report an unresolved symbol
error.  If the definition occurs in more than one object module, such as
because this template implementation header has been included in multiple
places, then the linker will report an error about duplicated symbols.  If
multiple object modules contain a function which calls itself
ConfigItemT<bool>::getString(), then the linker cannot know which function
it should use to resolve all the references which call that function.

If these were all declared inline, then the compiler could copy the code
for each function into all the places where the function is called.  That
avoids creating multiple definitions of the same symbol, because the
compiler does not need to create a function which can be called and whose
name must be resolved at link time.  However, that then increases the size
of the compiled code because of all the code duplication.

The C++ standard specifies how compilers should define code for template
instantiations, where and when, and how the inline keyword affects the
compiled code, and there are many complications and interactions.  So in general,
I think it's safest to use a template in one of two ways:

 Create one definition of all template instantiations, using a separate
 implementation header and explicit instantiation.  This is appropriate for
 templates which implement more complicated objects or interfaces, which
 are likely to be used with only a few well-known parameter types.  This is
 also appropriate for virtual subclasses, since there should be only one
 definition of the virtual methods for a particular template instantiation,
 and the compiler will automatically need to create a reference to that
 definition in the virtual table.

 Keep all the implementations in the same header file which defines the
 template.  This works well for general wrappers or adapter classes which
 are meant to work across many types, both native and user types.  The STL
 is an example.

 **/



#include <boost/lexical_cast.hpp>
#include <iostream>

template <typename T>
ConfigItemT<T>::
ConfigItemT(ConfigSet* cs, const std::string& name, const T& value) :
  ConfigItem(cs, name),
  _value(value)
{}

template <typename T>
void
ConfigItemT<T>::
setString(const std::string& value)
{
  _value = boost::lexical_cast<T>(value);
}

template <typename T>
bool
operator==(const T& lhs, const ConfigItemT<T>& rhs)
{
    return rhs == lhs;
}


template <typename T>
inline
std::string
ConfigItemT<T>::getString()
{
    std::ostringstream buf;
    buf << _value;
    return buf.str();
}


template <>
inline
std::string
ConfigItemT<std::string>::getString()
{
    return _value;
}


template <>
inline
std::string
ConfigItemT<bool>::getString()
{
    return _value ? "true" : "false";
}


template <>
inline
void
ConfigItemT<bool>::setString(const std::string& value)
{
    std::cerr << "ConfigItem<bool>::setString(" << value << ") called."
	      << std::endl;
    if (value == "true")
	_value = true;
    else if (value == "false")
	_value = false;
    else
	throw std::runtime_error(std::string("cannot convert ") +
				 value + " to bool");
}
