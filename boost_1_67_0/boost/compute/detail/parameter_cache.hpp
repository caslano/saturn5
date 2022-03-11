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