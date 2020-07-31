// -*- mode: C++; c-basic-offset: 4; -*-

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
