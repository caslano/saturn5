/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   current_thread_id.hpp
 * \author Andrey Semashev
 * \date   12.09.2009
 *
 * The header contains implementation of a current thread id attribute
 */

#ifndef BOOST_LOG_ATTRIBUTES_CURRENT_THREAD_ID_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_CURRENT_THREAD_ID_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_LOG_NO_THREADS)
#error Boost.Log: The current_thread_id attribute is only available in multithreaded builds
#endif

#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/log/detail/thread_id.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/attributes/attribute_value_impl.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Thread identifier type
typedef boost::log::aux::thread::id thread_id;

namespace attributes {

/*!
 * \brief A class of an attribute that always returns the current thread identifier
 *
 * \note This attribute can be registered globally, it will still return the correct
 *       thread identifier, no matter which thread emits the log record.
 */
class current_thread_id :
    public attribute
{
public:
    //! A held attribute value type
    typedef thread_id value_type;

protected:
    //! Factory implementation
    class BOOST_SYMBOL_VISIBLE impl :
        public attribute_value::impl
    {
    public:
        bool dispatch(type_dispatcher& dispatcher)
        {
            type_dispatcher::callback< value_type > callback =
                dispatcher.get_callback< value_type >();
            if (callback)
            {
                callback(boost::log::aux::this_thread::get_id());
                return true;
            }
            else
                return false;
        }

        intrusive_ptr< attribute_value::impl > detach_from_thread()
        {
            typedef attribute_value_impl< value_type > detached_value;
            return new detached_value(boost::log::aux::this_thread::get_id());
        }

        typeindex::type_index get_type() const { return typeindex::type_id< value_type >(); }
    };

public:
    /*!
     * Default constructor
     */
    current_thread_id() : attribute(new impl())
    {
    }
    /*!
     * Constructor for casting support
     */
    explicit current_thread_id(cast_source const& source) :
        attribute(source.as< impl >())
    {
    }
};

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_CURRENT_THREAD_ID_HPP_INCLUDED_

/* current_thread_id.hpp
PeVc/A/kPvP3SDd0V1e25jmvlD3N18/2i3udL13ceZ7o4/xpdJ3bo37eo/tl1V1Z5yFyD6C6K59z9gvefkyimXnN5ROqKHMGusJ5geesqXPV1BxZzY836XPEC/sBrHyXHeN2pyqkzUyQOXKL2d8ri9nkzDSMi+0vyDvMyDspy/OWOSuKtvcOKn9kTizzZMmbMJkL2MZ9cafyRI/75AdmZn7Y+qIm/Cdrs0LgatjL7Our2OuKdEVSV3ro8nesK7h3bp/yjEHsu1jrjHbjVDdOeZV3hjkB1t+s7FYVd+zyaUjIacgzyGV5Vp+k3jLJOCdxzRe/AoO869lJzC3P2HRcv1DxGm45MzCLE3nHT06dkFP4fbmqsl5Ku8+gXRd+q+4uZX+YOAYb05FfI52pj2HYbZY6+Ah8FNki1xsRyLVeg6LmCJ9WK5xjJvrxXqCHrb6Vc+jDT9nqG32PyifyT88TxL3KJ/KusB6Kn/LMy2teGdHUuf/PrmCrXyVYE5ddgr4/u4R9f3YJ+v7s/6K+35PfK5u5A8uQvULpsr4m3Kvv55MPLLPxZ21NeGX/1tZY9eTeT8+9kpVdZfI0wPq99DTrc7/2SieJ+hFjn4Pr87UbKp3B9F3MqhGLX6mG5YzBeKXX0WhEzOIR+WaNrANzy7VY/8+187VGx5rvu1u4HV6QMfc80hK9gkre+S5Drl/jLW513b0aaX0O51jX0f/PjrncWxYZcxsZo1Q8l1WWMVf6tnU/YtzdHG4Zd53n5PoZK/mlnzP9nOMseaDHWWv9uNLKnZivpe/4EkkgwVvCbPVDhtmwwjKf5KsfxK3vMVbbR1vriHZje7eqn0c9r+x/Z7RlfPolNdlXnXF4N6rb8vfKj76EHC1m3MmruhnBHXeA3N97jcu6jR9Wbk8bCaRwK2Ibp/V7WpfybxVf8q6g03tQuf3QsIzhun7K2bh6rNXvw2Q9zGfV3GfNJ1me35Qrrm+gPpIm2/MbXe8m+ejXneuc6NnGVBVvpzF1YmvnMTW5gq0uqSHVv/up5BKMqcklHFOTSzCmJv8XjqnJCXJ+iqR/L/IKZvkNLPltlmS8+42dXoOn51Ly3Relv1S9jUo0Bsp3GTz+PEl5RtPmAq3lInYu/W7EJfXDs+bkY2Uf4VhOuHV+JiJt/fcS7gLRkb5+Cv/puP1V6awnZkMNvhRiX/+pn8m2bCjvDNU1KyDUdXOktn7WxfMW3kMUfnf5E70m1DMWXP9ZlzkO5DZ0Hgec2pSlH9d60o+TTu81mZcTin5781Zzrupem0xb4ivX6oOk/t0v485al0mf/3UZvx3Xja5v4/08uZKsB9sTYY1jTuacDP+eGeHOK46fx/ofR19rvK/INw8Gi6NB8vxwtbt/4uaJOKpJf8meH66u4P/zw9UVSvb8EP0ibcU6P31U2bc36lmeH276Dz0/PNfO8fkhCbHnb8meHxqh/j8/FF1db7aUoJ/25/nhZcyiA32fe+x8DrDv858/qmiaJ/29SeNh38xdurvPqOgLZVfc7ftc6KsHTfN+PX/dK6X9D8siH2s+59Pcjtz89wszzY+9PeKznZNrnv/HA1t6vl//WTa/t6hkmu/5ZGTdDWOfDFlc4ZQr6psdbLLvo8LNrXHP1wuGbBy1uOmtj7A7/Zzv85k5YwLzX95yIqjiku+errfvd/WaPNK/s+/zru9T51d//9Ko4afzbtuR9t2EXq91OPeS7/OlN0wwzc8uTF+1vdpX+89Hpn18ctFLTX2dI+37XOsqKl2Ldjz87qevxMUteOXmvMx7t18o+TneJT1f2te53A8kKv+TN/c6/+TkNqub57/xt+/vbfzTnTvtfO637/O9nc/x9nU=
*/