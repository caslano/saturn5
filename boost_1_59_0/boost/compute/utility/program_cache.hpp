//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_UTILITY_PROGRAM_CACHE_HPP
#define BOOST_COMPUTE_UTILITY_PROGRAM_CACHE_HPP

#include <string>
#include <utility>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>

#include <boost/compute/context.hpp>
#include <boost/compute/program.hpp>
#include <boost/compute/detail/lru_cache.hpp>
#include <boost/compute/detail/global_static.hpp>

namespace boost {
namespace compute {

/// The program_cache class stores \ref program objects in a LRU cache.
///
/// This class can be used to help mitigate the overhead of OpenCL's run-time
/// kernel compilation model. Commonly used programs can be stored persistently
/// in the cache and only compiled once on their first use.
///
/// Program objects are stored and retreived based on a user-defined cache key
/// along with the options used to build the program (if any).
///
/// For example, to insert a program into the cache:
/// \code
/// cache.insert("foo", foo_program);
/// \endcode
///
/// And to retreive the program later:
/// \code
/// boost::optional<program> p = cache.get("foo");
/// if(p){
///     // program found in cache
/// }
/// \endcode
///
/// \see program
class program_cache : boost::noncopyable
{
public:
    /// Creates a new program cache with space for \p capacity number of
    /// program objects.
    program_cache(size_t capacity)
        : m_cache(capacity)
    {
    }

    /// Destroys the program cache.
    ~program_cache()
    {
    }

    /// Returns the number of program objects currently stored in the cache.
    size_t size() const
    {
        return m_cache.size();
    }

    /// Returns the total capacity of the cache.
    size_t capacity() const
    {
        return m_cache.capacity();
    }

    /// Clears the program cache.
    void clear()
    {
        m_cache.clear();
    }

    /// Returns the program object with \p key. Returns a null optional if no
    /// program with \p key exists in the cache.
    boost::optional<program> get(const std::string &key)
    {
        return m_cache.get(std::make_pair(key, std::string()));
    }

    /// Returns the program object with \p key and \p options. Returns a null
    /// optional if no program with \p key and \p options exists in the cache.
    boost::optional<program> get(const std::string &key, const std::string &options)
    {
        return m_cache.get(std::make_pair(key, options));
    }

    /// Inserts \p program into the cache with \p key.
    void insert(const std::string &key, const program &program)
    {
        insert(key, std::string(), program);
    }

    /// Inserts \p program into the cache with \p key and \p options.
    void insert(const std::string &key, const std::string &options, const program &program)
    {
        m_cache.insert(std::make_pair(key, options), program);
    }

    /// Loads the program with \p key from the cache if it exists. Otherwise
    /// builds a new program with \p source and \p options, stores it in the
    /// cache, and returns it.
    ///
    /// This is a convenience function to simplify the common pattern of
    /// attempting to load a program from the cache and, if not present,
    /// building the program from source and storing it in the cache.
    ///
    /// Equivalent to:
    /// \code
    /// boost::optional<program> p = get(key, options);
    /// if(!p){
    ///     p = program::create_with_source(source, context);
    ///     p->build(options);
    ///     insert(key, options, *p);
    /// }
    /// return *p;
    /// \endcode
    program get_or_build(const std::string &key,
                         const std::string &options,
                         const std::string &source,
                         const context &context)
    {
        boost::optional<program> p = get(key, options);
        if(!p){
            p = program::build_with_source(source, context, options);

            insert(key, options, *p);
        }
        return *p;
    }

    /// Returns the global program cache for \p context.
    ///
    /// This global cache is used internally by Boost.Compute to store compiled
    /// program objects used by its algorithms. All Boost.Compute programs are
    /// stored with a cache key beginning with \c "__boost". User programs
    /// should avoid using the same prefix in order to prevent collisions.
    static boost::shared_ptr<program_cache> get_global_cache(const context &context)
    {
        typedef detail::lru_cache<cl_context, boost::shared_ptr<program_cache> > cache_map;

        BOOST_COMPUTE_DETAIL_GLOBAL_STATIC(cache_map, caches, (8));

        boost::optional<boost::shared_ptr<program_cache> > cache = caches.get(context.get());
        if(!cache){
            cache = boost::make_shared<program_cache>(64);

            caches.insert(context.get(), *cache);
        }

        return *cache;
    }

private:
    detail::lru_cache<std::pair<std::string, std::string>, program> m_cache;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_UTILITY_PROGRAM_CACHE_HPP

/* program_cache.hpp
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
*/