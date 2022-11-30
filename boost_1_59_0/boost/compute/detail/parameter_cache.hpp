//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_PARAMETER_CACHE_HPP
#define BOOST_COMPUTE_DETAIL_PARAMETER_CACHE_HPP

#include <algorithm>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/device.hpp>
#include <boost/compute/detail/global_static.hpp>
#include <boost/compute/version.hpp>

#ifdef BOOST_COMPUTE_USE_OFFLINE_CACHE
#include <cstdio>  
#include <boost/algorithm/string/trim.hpp>
#include <boost/compute/detail/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#endif // BOOST_COMPUTE_USE_OFFLINE_CACHE

namespace boost {
namespace compute {
namespace detail {

class parameter_cache : boost::noncopyable
{
public:
    parameter_cache(const device &device)
        : m_dirty(false),
          m_device_name(device.name())
    {
    #ifdef BOOST_COMPUTE_USE_OFFLINE_CACHE
        // get offline cache file name (e.g. /home/user/.boost_compute/tune/device.json)
        m_file_name = make_file_name();

        // load parameters from offline cache file (if it exists)
        if(boost::filesystem::exists(m_file_name)){
            read_from_disk();
        }
    #endif // BOOST_COMPUTE_USE_OFFLINE_CACHE
    }

    ~parameter_cache()
    {
    #ifdef BOOST_COMPUTE_USE_OFFLINE_CACHE
        write_to_disk();
    #endif // BOOST_COMPUTE_USE_OFFLINE_CACHE
    }

    void set(const std::string &object, const std::string &parameter, uint_ value)
    {
        m_cache[std::make_pair(object, parameter)] = value;

        // set the dirty flag to true. this will cause the updated parameters
        // to be stored to disk.
        m_dirty = true;
    }

    uint_ get(const std::string &object, const std::string &parameter, uint_ default_value)
    {
        std::map<std::pair<std::string, std::string>, uint_>::iterator
            iter = m_cache.find(std::make_pair(object, parameter));
        if(iter != m_cache.end()){
            return iter->second;
        }
        else {
            return default_value;
        }
    }

    static boost::shared_ptr<parameter_cache> get_global_cache(const device &device)
    {
        // device name -> parameter cache
        typedef std::map<std::string, boost::shared_ptr<parameter_cache> > cache_map;

        BOOST_COMPUTE_DETAIL_GLOBAL_STATIC(cache_map, caches, ((std::less<std::string>())));

        cache_map::iterator iter = caches.find(device.name());
        if(iter == caches.end()){
            boost::shared_ptr<parameter_cache> cache =
                boost::make_shared<parameter_cache>(device);

            caches.insert(iter, std::make_pair(device.name(), cache));

            return cache;
        }
        else {
            return iter->second;
        }
    }

private:
#ifdef BOOST_COMPUTE_USE_OFFLINE_CACHE
    // returns a string containing a cannoical device name
    static std::string cannonical_device_name(std::string name)
    {
        boost::algorithm::trim(name);
        std::replace(name.begin(), name.end(), ' ', '_');
        std::replace(name.begin(), name.end(), '(', '_');
        std::replace(name.begin(), name.end(), ')', '_');
        return name;
    }

    // returns the boost.compute version string
    static std::string version_string()
    {
        char buf[32];
        // snprintf is in Visual Studio since Visual Studio 2015 (_MSC_VER == 1900)
        #if defined (_MSC_VER) && _MSC_VER < 1900
            #define DETAIL_SNPRINTF sprintf_s
        #else
            #define DETAIL_SNPRINTF std::snprintf
        #endif
        DETAIL_SNPRINTF(buf, sizeof(buf), "%d.%d.%d", BOOST_COMPUTE_VERSION_MAJOR,
                                                      BOOST_COMPUTE_VERSION_MINOR,
                                                      BOOST_COMPUTE_VERSION_PATCH);
        #undef DETAIL_SNPRINTF
        return buf;
    }

    // returns the file path for the cached parameters
    std::string make_file_name() const
    {
        return detail::parameter_cache_path(true) + cannonical_device_name(m_device_name) + ".json";
    }

    // store current parameters to disk
    void write_to_disk()
    {
        BOOST_ASSERT(!m_file_name.empty());

        if(m_dirty){
            // save current parameters to disk
            boost::property_tree::ptree pt;
            pt.put("header.device", m_device_name);
            pt.put("header.version", version_string());
            typedef std::map<std::pair<std::string, std::string>, uint_> map_type;
            for(map_type::const_iterator iter = m_cache.begin(); iter != m_cache.end(); ++iter){
                const std::pair<std::string, std::string> &key = iter->first;
                pt.add(key.first + "." + key.second, iter->second);
            }
            write_json(m_file_name, pt);

            m_dirty = false;
        }
    }

    // load stored parameters from disk
    void read_from_disk()
    {
        BOOST_ASSERT(!m_file_name.empty());

        m_cache.clear();

        boost::property_tree::ptree pt;
        try {
            read_json(m_file_name, pt);
        }
        catch(boost::property_tree::json_parser::json_parser_error&){
            // no saved cache file, ignore
            return;
        }

        std::string stored_device;
        try {
            stored_device = pt.get<std::string>("header.device");
        }
        catch(boost::property_tree::ptree_bad_path&){
            return;
        }

        std::string stored_version;
        try {
            stored_version = pt.get<std::string>("header.version");
        }
        catch(boost::property_tree::ptree_bad_path&){
            return;
        }

        if(stored_device == m_device_name && stored_version == version_string()){
            typedef boost::property_tree::ptree::const_iterator pt_iter;
            for(pt_iter iter = pt.begin(); iter != pt.end(); ++iter){
                if(iter->first == "header"){
                    // skip header
                    continue;
                }

                boost::property_tree::ptree child_pt = pt.get_child(iter->first);
                for(pt_iter child_iter = child_pt.begin(); child_iter != child_pt.end(); ++child_iter){
                    set(iter->first, child_iter->first, boost::lexical_cast<uint_>(child_iter->second.data()));
                }
            }
        }

        m_dirty = false;
    }
#endif // BOOST_COMPUTE_USE_OFFLINE_CACHE

private:
    bool m_dirty;
    std::string m_device_name;
    std::string m_file_name;
    std::map<std::pair<std::string, std::string>, uint_> m_cache;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_PARAMETER_CACHE_HPP

/* parameter_cache.hpp
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
*/