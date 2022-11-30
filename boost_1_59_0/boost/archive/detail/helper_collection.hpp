#ifndef BOOST_ARCHIVE_DETAIL_HELPER_COLLECTION_HPP
#define BOOST_ARCHIVE_DETAIL_HELPER_COLLECTION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// helper_collection.hpp: archive support for run-time helpers

// (C) Copyright 2002-2008 Robert Ramey and Joaquin M Lopez Munoz
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstddef> // NULL
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>

#include <boost/config.hpp>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>

namespace boost {

namespace archive {
namespace detail {

class helper_collection
{
    helper_collection(const helper_collection&);              // non-copyable
    helper_collection& operator = (const helper_collection&); // non-copyable

    // note: we dont' actually "share" the function object pointer
    // we only use shared_ptr to make sure that it get's deleted

    typedef std::pair<
        const void *,
        boost::shared_ptr<void>
    > helper_value_type;
    template<class T>
    boost::shared_ptr<void> make_helper_ptr(){
        // use boost::shared_ptr rather than std::shared_ptr to maintain
        // c++03 compatibility
        return boost::make_shared<T>();
    }

    typedef std::vector<helper_value_type> collection;
    collection m_collection;

    struct predicate {
        BOOST_DELETED_FUNCTION(predicate & operator=(const predicate & rhs))
    public:
        const void * const m_ti;
        bool operator()(helper_value_type const &rhs) const {
            return m_ti == rhs.first;
        }
        predicate(const void * ti) :
            m_ti(ti)
        {}
    };
protected:
    helper_collection(){}
    ~helper_collection(){}
public:
    template<typename Helper>
    Helper& find_helper(void * const id = 0) {
        collection::const_iterator it =
            std::find_if(
                m_collection.begin(),
                m_collection.end(),
                predicate(id)
            );

        void * rval = 0;
        if(it == m_collection.end()){
            m_collection.push_back(
                std::make_pair(id, make_helper_ptr<Helper>())
            );
            rval = m_collection.back().second.get();
        }
        else{
            rval = it->second.get();
        }
        return *static_cast<Helper *>(rval);
    }
};

} // namespace detail
} // namespace serialization
} // namespace boost

#endif // BOOST_ARCHIVE_DETAIL_HELPER_COLLECTION_HPP

/* helper_collection.hpp
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
*/