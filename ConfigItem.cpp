// -*- mode: C++; c-basic-offset: 4; -*-

#include "ConfigItem.h"

#include "ConfigItem_impl.h"

ConfigSet::
ConfigSet()
{}


ConfigItem::
ConfigItem(ConfigSet* cs, const std::string& name) :
  _name(name), _cs(cs)
{}



template class ConfigItemT<bool>;
template class ConfigItemT<int>;
template class ConfigItemT<float>;
template class ConfigItemT<std::string>;

template bool operator==<bool>(const bool& lhs, const ConfigItemT<bool>& rhs);
template bool operator==<int>(const int& lhs, const ConfigItemT<int>& rhs);
template bool operator==<float>(const float& lhs, const ConfigItemT<float>& rhs);
template bool operator==<std::string>(const std::string& lhs,
				      const ConfigItemT<std::string>& rhs);

