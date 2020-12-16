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
gn7wEgyBUUAgQ98DDMACyoANuIAH+EAAzIADcAJuwB14Ax/gBwJAIAgGYSASRIE1YB1IAikgHWSCLJADcsEhUARKQTmoAtWgFtSDBtAEWkAraAMdoBs8An1gAAyCIUCgQN8Dd+H4ToSahv6+549/LB/Lx/Kx/KeVvz3+ZHyA299xn+jxEYX2WuOLjw1JjQlbsSwMbg85Fv/lVZPvU+3k7OLqNuV3bcefD6AZf87prz+biG0mTcL4yfGbxC4S/N3rHxuO+Y+MzxkbdvqPvG58xOLvuy/eu9fBUNPfvp8cS+WD11HtnIirjJkUn6n0Lq41blJc+V3cZMyk+FWVd3HHcZPiau/iC8ZNirPfxTeMmxTnqnxwfNuPfyF+98Nx+HdUz1kR+1yOv0tc0ltr75G9R5dnvGi4ITq7bCXB7nTvkidzZRcvHhTUJas0rhFk+W6cFlASVvRix5UTN2cHHW85H9B0e/MC9mfTdtzfWjHz3o/Nd++e+/Imc6rE+nri490x7TE340J0v/5EfGAfzW40NiVo5YKHdamvqa/Mvr65vbSoglr8tHLIoultZ1yjJ2/vtDSGCmvgnLPOtgPd2/a575o/ysHOMxaUnXwk2pJw8kxB53S9tUnfll96OT3a+f62hGXrXIzjQzb9UK4jbRa18neb26Rj2pcPbvtaaD+ylZWb3ebj4TAj7k1JXWti0mx36YlTnbR9C7IUN6+quFBinnj1WeiTtVuw7T891N5b6Xtig8urq/slOz9lCVYvuO9RcM77TgN/uW+gV6DnJVWPoIKnZzZ88k3mC/ah1so1B5U3GfSXrObbVBTb9WVHj07fx5HPZzzfcfPNys6QrNjZgbMieHcs7q/O+RF3oeyrE8Otj15ZfBu1sfbqkYE9cwx+JNeu0cBf+lrgcwUXPSOl+MHqLvxO/oKgP5SKBluHDXGvn1yL5a/On7+u+ZhOGc9t9tT4V188MM32V5uinEKquNafuGiZy2qtqjilDcM82+MZFyXxiuGumvrsfPvaZqerftExoy9aqTH0I4/nZzxJWzXkezKNJtpdoCJ4ePR18zBBbXGprdJe5fQFjcdCy3vDbMgPZ47gbxdMTbhMF+M8ChV4zdLc0PjYu2mJvZn7jzcIovNmLiiTfvWl+A3paYpqyImVxaJPNzPn31ncn7V3uqlTa/g3oxPl4jXbAq2mjR475EbuvvFvdREXdsXs94LLw6fcOnX2C0r8soCg1XOVOypltNYoqwg5sxYtvWAfjY37cRF5yy3ia1F/+NNranrXOq9kB+lOv/vVNs0WM0rrtm8HC8/f7ziczMgoXSdDDJgb9XgLta/1U3zy8JNFpzTaC7m+R8xWz8TTlc2KjH44umXejpUsOcLrPSp611hdS9Mfr52WbqOi/Gn6zw3CO/WzPol8FlBXlnqA9ORAEj8Lt0lWxTB+X6fkiqXxlPk7TddyVS6Sl8X04/ecnj7DQiY0YvfuFSRB877KWclacwYWauwuyvuJFxCSFNioM3LEQSls73VfDcupt/cQqoNzT65F30v97z/xXqw/7QHHY628Ts63h3I2zxsOt37aW058ceKzUVp4r9XhR86fvDi3fv7CuLLk+27fe0dEWHR4WSkGPo+gCk3UXWwvl6qm97XhzXesIk/31s5iSg6foWFjLoVuIc/ACpo0ftqwdeG5H8y/X8I9cJtRP/peyRQTzestXnimnj2886fy0U01banb9zw+nlYw71gzfxfxqsbUFdy4NvWTxS33rqwQBHF6u/29N+VKeAdqd+732v1dZsDZ8Bnufmv1D188w1F8s8N4aMcdfOv3la0PP7lhcPFRku5tGuuE+ZKv1OzuvViqwq/N1PM=
*/