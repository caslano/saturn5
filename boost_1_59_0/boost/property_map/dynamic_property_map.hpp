#ifndef BOOST_PROPERTY_MAP_DYNAMIC_PROPERTY_MAP_HPP
#define BOOST_PROPERTY_MAP_DYNAMIC_PROPERTY_MAP_HPP

// Copyright 2004-5 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  dynamic_property_map.hpp -
//    Support for runtime-polymorphic property maps.  This header is factored
//  out of Doug Gregor's routines for reading GraphML files for use in reading
//  GraphViz graph files.

//  Authors: Doug Gregor
//           Ronald Garcia
//


#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/any.hpp>
#include <boost/function/function3.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <typeinfo>
#include <boost/mpl/bool.hpp>
#include <stdexcept>
#include <sstream>
#include <map>
#include <boost/type.hpp>
#include <boost/smart_ptr.hpp>

namespace boost {

namespace detail {

  // read_value -
  //   A wrapper around lexical_cast, which does not behave as
  //   desired for std::string types.
  template<typename Value>
  inline Value read_value(const std::string& value)
  { return boost::lexical_cast<Value>(value); }

  template<>
  inline std::string read_value<std::string>(const std::string& value)
  { return value; }

}


// dynamic_property_map -
//  This interface supports polymorphic manipulation of property maps.
class dynamic_property_map
{
public:
  virtual ~dynamic_property_map() { }

  virtual boost::any get(const any& key) = 0;
  virtual std::string get_string(const any& key) = 0;
  virtual void put(const any& key, const any& value) = 0;
  virtual const std::type_info& key() const = 0;
  virtual const std::type_info& value() const = 0;
};


//////////////////////////////////////////////////////////////////////
// Property map exceptions
//////////////////////////////////////////////////////////////////////

struct dynamic_property_exception : public std::exception {
  virtual ~dynamic_property_exception() throw() {}
  virtual const char* what() const throw() = 0;
};

struct property_not_found : public dynamic_property_exception {
  std::string property;
  mutable std::string statement;
  property_not_found(const std::string& property) : property(property) {}
  virtual ~property_not_found() throw() {}

  const char* what() const throw() {
    if(statement.empty())
      statement =
        std::string("Property not found: ") + property + ".";

    return statement.c_str();
  }
};

struct dynamic_get_failure : public dynamic_property_exception {
  std::string property;
  mutable std::string statement;
  dynamic_get_failure(const std::string& property) : property(property) {}
  virtual ~dynamic_get_failure() throw() {}

  const char* what() const throw() {
    if(statement.empty())
      statement =
        std::string(
         "dynamic property get cannot retrieve value for  property: ")
        + property + ".";

    return statement.c_str();
  }
};

struct dynamic_const_put_error  : public dynamic_property_exception {
  virtual ~dynamic_const_put_error() throw() {}

  const char* what() const throw() {
    return "Attempt to put a value into a const property map: ";
  }
};


namespace detail {

// Trying to work around VC++ problem that seems to relate to having too many
// functions named "get"
template <typename PMap, typename Key>
typename boost::property_traits<PMap>::reference
get_wrapper_xxx(const PMap& pmap, const Key& key) {
  using boost::get;
  return get(pmap, key);
}

//
// dynamic_property_map_adaptor -
//   property-map adaptor to support runtime polymorphism.
template<typename PropertyMap>
class dynamic_property_map_adaptor : public dynamic_property_map
{
  typedef typename property_traits<PropertyMap>::key_type key_type;
  typedef typename property_traits<PropertyMap>::value_type value_type;
  typedef typename property_traits<PropertyMap>::category category;

  // do_put - overloaded dispatches from the put() member function.
  //   Attempts to "put" to a property map that does not model
  //   WritablePropertyMap result in a runtime exception.

  //   in_value must either hold an object of value_type or a string that
  //   can be converted to value_type via iostreams.
  void do_put(const any& in_key, const any& in_value, mpl::bool_<true>)
  {
    using boost::put;

    key_type key_ = any_cast<key_type>(in_key);
    if (in_value.type() == typeid(value_type)) {
      put(property_map_, key_, any_cast<value_type>(in_value));
    } else {
      //  if in_value is an empty string, put a default constructed value_type.
      std::string v = any_cast<std::string>(in_value);
      if (v.empty()) {
        put(property_map_, key_, value_type());
      } else {
        put(property_map_, key_, detail::read_value<value_type>(v));
      }
    }
  }

  void do_put(const any&, const any&, mpl::bool_<false>)
  {
    BOOST_THROW_EXCEPTION(dynamic_const_put_error());
  }

public:
  explicit dynamic_property_map_adaptor(const PropertyMap& property_map_)
    : property_map_(property_map_) { }

  virtual boost::any get(const any& key_)
  {
    return get_wrapper_xxx(property_map_, any_cast<typename boost::property_traits<PropertyMap>::key_type>(key_));
  }

  virtual std::string get_string(const any& key_)
  {
    std::ostringstream out;
    out << get_wrapper_xxx(property_map_, any_cast<typename boost::property_traits<PropertyMap>::key_type>(key_));
    return out.str();
  }

  virtual void put(const any& in_key, const any& in_value)
  {
    do_put(in_key, in_value,
           mpl::bool_<(is_convertible<category*,
                                      writable_property_map_tag*>::value)>());
  }

  virtual const std::type_info& key()   const { return typeid(key_type); }
  virtual const std::type_info& value() const { return typeid(value_type); }

  PropertyMap&       base()       { return property_map_; }
  const PropertyMap& base() const { return property_map_; }

private:
  PropertyMap property_map_;
};

} // namespace detail

//
// dynamic_properties -
//   container for dynamic property maps
//
struct dynamic_properties
{
  typedef std::multimap<std::string, boost::shared_ptr<dynamic_property_map> >
    property_maps_type;
  typedef boost::function3<boost::shared_ptr<dynamic_property_map>,
                           const std::string&,
                           const boost::any&,
                           const boost::any&> generate_fn_type;
public:

  typedef property_maps_type::iterator iterator;
  typedef property_maps_type::const_iterator const_iterator;

  dynamic_properties() : generate_fn() { }
  dynamic_properties(const generate_fn_type& g) : generate_fn(g) {}

  ~dynamic_properties() {}

  template<typename PropertyMap>
  dynamic_properties&
  property(const std::string& name, PropertyMap property_map_)
  {
    boost::shared_ptr<dynamic_property_map> pm(
      boost::static_pointer_cast<dynamic_property_map>(
        boost::make_shared<detail::dynamic_property_map_adaptor<PropertyMap> >(property_map_)));
    property_maps.insert(property_maps_type::value_type(name, pm));

    return *this;
  }

  template<typename PropertyMap>
  dynamic_properties
  property(const std::string& name, PropertyMap property_map_) const
  {
    dynamic_properties result = *this;
    result.property(name, property_map_);
    return result;
  }

  iterator       begin()       { return property_maps.begin(); }
  const_iterator begin() const { return property_maps.begin(); }
  iterator       end()         { return property_maps.end(); }
  const_iterator end() const   { return property_maps.end(); }

  iterator lower_bound(const std::string& name)
  { return property_maps.lower_bound(name); }

  const_iterator lower_bound(const std::string& name) const
  { return property_maps.lower_bound(name); }

  void
  insert(const std::string& name, boost::shared_ptr<dynamic_property_map> pm)
  {
    property_maps.insert(property_maps_type::value_type(name, pm));
  }

  template<typename Key, typename Value>
  boost::shared_ptr<dynamic_property_map>
  generate(const std::string& name, const Key& key, const Value& value)
  {
    if(!generate_fn) {
      BOOST_THROW_EXCEPTION(property_not_found(name));
    } else {
      return generate_fn(name,key,value);
    }
  }

private:
  property_maps_type property_maps;
  generate_fn_type generate_fn;
};

template<typename Key, typename Value>
bool
put(const std::string& name, dynamic_properties& dp, const Key& key,
    const Value& value)
{
  for (dynamic_properties::iterator i = dp.lower_bound(name);
       i != dp.end() && i->first == name; ++i) {
    if (i->second->key() == typeid(key)) {
      i->second->put(key, value);
      return true;
    }
  }

  boost::shared_ptr<dynamic_property_map> new_map = dp.generate(name, key, value);
  if (new_map.get()) {
    new_map->put(key, value);
    dp.insert(name, new_map);
    return true;
  } else {
    return false;
  }
}

template<typename Value, typename Key>
Value
get(const std::string& name, const dynamic_properties& dp, const Key& key)
{
  for (dynamic_properties::const_iterator i = dp.lower_bound(name);
       i != dp.end() && i->first == name; ++i) {
    if (i->second->key() == typeid(key))
      return any_cast<Value>(i->second->get(key));
  }

  BOOST_THROW_EXCEPTION(dynamic_get_failure(name));
}

template<typename Value, typename Key>
Value
get(const std::string& name, const dynamic_properties& dp, const Key& key, type<Value>)
{
  for (dynamic_properties::const_iterator i = dp.lower_bound(name);
       i != dp.end() && i->first == name; ++i) {
    if (i->second->key() == typeid(key))
      return any_cast<Value>(i->second->get(key));
  }

  BOOST_THROW_EXCEPTION(dynamic_get_failure(name));
}

template<typename Key>
std::string
get(const std::string& name, const dynamic_properties& dp, const Key& key)
{
  for (dynamic_properties::const_iterator i = dp.lower_bound(name);
       i != dp.end() && i->first == name; ++i) {
    if (i->second->key() == typeid(key))
      return i->second->get_string(key);
  }

  BOOST_THROW_EXCEPTION(dynamic_get_failure(name));
}

// The easy way to ignore properties.
inline
boost::shared_ptr<boost::dynamic_property_map>
ignore_other_properties(const std::string&,
                        const boost::any&,
                        const boost::any&) {
  return boost::shared_ptr<boost::dynamic_property_map>();
}

} // namespace boost

#endif // BOOST_PROPERTY_MAP_DYNAMIC_PROPERTY_MAP_HPP

/* dynamic_property_map.hpp
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
*/