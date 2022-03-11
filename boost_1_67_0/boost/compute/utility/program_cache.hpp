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