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
qIuTKXLoxjCSk12DftRMYdNYhT7ENtFXNKETZUyt0Q60oXZT/UYO/Qh/4Dta0IPwh+pDLyprlYMCuv41Koj+Oco6AHy2f+nzU+9x19vHFUl/L0Qriqj4bFQwHf2v+ft1e7uiBf2oW2evWKzBMGb22T8W3ah4w3c0oRfxN72HihasRe1b6kEHypjaryx0Inh7VJDCMnSh4h31ogX9SLzrWqxBUPKePXLoQ+K9UUEj2lBC/fvWxrAGG5D6YFTQjCJqBswB0Ia1qP3QvYiwAbM+Ui56EftYPcihD4lB1yLCMGZ9Yh6Iea9o25PajXiXv9GJBZHz6EL3vfpzj3IucX2rfqJmpWMoWsvL+ozllI9W1K83f1pO3te6HhWXki0akUcPKi4bFTRgzsXKQ4S6XziGrvPJzWdG2Xks9z28gCyQRxldNrcdRPxccj5Uu33OOlu7zqKn08joZOV9xP8PpzMMoPYI53bVJp859GAY0+a6HxvkBl0+h5BocB06UEL8J6OC+cihF+FP1YdliDCIqUeOCpagHWtRN08f0IXKo/QNy9COPsxU32KsQsd07ZjB/tCPaXvCekswx30Y0sda39fsp/9I7O/492zrHp8dWIu2t91zgHvRiFUYQP0sbUEb1qLiQNegCYl37BvqcxALD9JHTPuCLHwOIHYwn8JM8mzfxf0IyDGJFvSicpp7sAAdWF/jXp/TdnMN+lC7O/mgF4k9/I1exKe7D01o/ECOltTuPvun+lyCVcg63orWenrCMv1eg+wo+vEZbqd9aEQruhFsTydoRB59iE2lNyxDJ8qo24FukUM31iOxI/2jGV0oo/9Hrvmxa7AeiS39TSdhNTvGUrSjYpJ+oxEt6MEG1MWViWZ0YhDTJ5M5VqEb61E/hTzQij7UbMLvUURYo/3IoYCpm+oTvfRrx3p0kEfxO7KzZphBG2oD/cUGrB2hjJHaiyz6XF9Rob1oRBv6ERtNnliKCCXExqgbS9GOEpIbaRtasMFeVH0+Kypdhxz6UTdWH5FHcmN9w2JtbfwO2rNmJOg2+SFf+EYZGP6H//MljjShE4Oo/craI5qwBoNI/NMe2ViFIir/Zc+5v+m/z2FlzlFOr88BRJ+TE2LOL0MnGrSjHUPqzpBj+k3XoR+Vb9nPCksRobLfvsBoRCcGUcPfZmH4dXa7zv3IYS1q+9SP+Fp78Ppcj9n23im9qlzHlmANBhEV3YPwZfcgjxISryj/RfcjeEn9aP0r38QGTHtee5DHfPtdNqMLbT3KxeLfO4ciKp50PTJoQz9iXdqEZYjQj/AP6sFirEIfYn+kjyfciw2PumYNGaMRBQxi5mP6jn5URvb6xALkUPEwGd2p3ru0BRuQaFMeVmEIvXfr52X62aTPaEYRweXajYVoQQ8qriBDLMMarEf9lWSA5ejGBtQ10wlasRaVVykby9CJ9Zh6tX4gj37UXqMctKAbFcv1DUvRhn6E19ITlqMHwQoywxJ0YAA1K8kMzShgA5I5ckUb+hG/TjnIohPDSF5PLujAEJI3uAcdGEBdiz6hA0OYeqN60YEB1N2kP2hDCYmb9QVFzGrVdxSwATNv4U/oQhn1tyobRdTcpv1oQRHhKrpEL2K/URZy6EV8NV2jFSXU364P6EBd3nGsn+3vQxxHG4ZQe6i2ow0DiB9Gz2hBLzZg2hzHsAYDSB6uf2hHP6Yeoc2IUEL9XG1BOwYQb2DjaEIXyqj7iWvQih5U/JQssAQdGEDNkXSDZnRjA2bOIz9EKGPaUerBIOqO1g7kMYhpx+grOjCAuvlsHQOoO1YfEGEIyeN8RwcGkTxen5HDnLT7MID6n2kjulBxMh2gCRFKiJ3CL9CMNRg=
*/