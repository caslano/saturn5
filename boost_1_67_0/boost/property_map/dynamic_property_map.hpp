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