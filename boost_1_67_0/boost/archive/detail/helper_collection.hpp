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