//Copyright (c) 2006-2010 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_CE6983AC753411DDA764247956D89593
#define BOOST_EXCEPTION_CE6983AC753411DDA764247956D89593

#include <boost/config.hpp>
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
#include <boost/type_traits/is_nothrow_move_constructible.hpp>
#endif
#include <utility>
#include <string>

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    namespace
    exception_detail
        {
        class
        error_info_base
            {
            public:

            virtual std::string name_value_string() const = 0;
            virtual error_info_base * clone() const = 0;

            virtual
            ~error_info_base() BOOST_NOEXCEPT_OR_NOTHROW
                {
                }
            };
        }

    template <class Tag,class T>
    class
    error_info:
        public exception_detail::error_info_base
        {
        exception_detail::error_info_base *
        clone() const
            {
            return new error_info<Tag,T>(*this);
            }
        public:
        typedef T value_type;
        error_info( value_type const & v ):
            v_(v)
            {
            }
#if (__GNUC__*100+__GNUC_MINOR__!=406) //workaround for g++ bug
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        error_info( error_info const & x ):
            v_(x.v_)
            {
            }
        error_info( T && v ) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible<T>::value):
            v_(std::move(v))
            {
            }
        error_info( error_info && x ) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible<T>::value):
            v_(std::move(x.v_))
            {
            }
#endif
#endif
        ~error_info() BOOST_NOEXCEPT_OR_NOTHROW
            {
            }
        value_type const &
        value() const
            {
            return v_;
            }
        value_type &
        value()
            {
            return v_;
            }
        private:
        error_info & operator=( error_info const & );
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
        error_info & operator=( error_info && x );
#endif
        std::string name_value_string() const;
        value_type v_;
        };
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* error_info_impl.hpp
Ie0CZeOATl4MGCV4J++rD2Mc+F7kAg+qo7iD/QxFfs1jkYakmUR69fXKWkVaGCtFKgDyRqJFJIruW33VT7WJdOUHkURKkiIV1CJSixCRPiKf4De+UiJNHUwiPUsijfiodpEei5Ei3e9CP9avrSKtcOHd9RO1ibTq/UgijXKRSOuckUUa2swiUqAVjVkcS5ujqsQvGQ4FRGCA+KXfCvkoyhBh2g1TohDlTbrhQk/NqDvF9CABjEMgPIbgltGZpoANieRHIFqc07od6GQ6Ci7MBNzjskopDWHzICHTyEM7loqCUE5Dp//vOHQ2Nw+d6WAJqM4E5IHMzBIkXxp8pj2vBiYaxvISYXGFw/LNl4DlZ6yd4XpsNBK8wpAyvMeqI2N0pYkvlGC5P1VNFoD9EGnNXd8orVkMhhOeXvhthtmQTySukPm5lP8G5V8i8/ON4ZDP+KtP4LOe7DqcHByYChM1/YhTv2GA7KypZHuPjBvWkmc+nNacPFuvAeM0tM48R+GUcPGvCMuD0TL4VZfgHc4aSCP1pjskgCewjyc0KJ2m/IsTonkORXmPkLxTeb4Z2w6vnn1NydmYTMosko9ScvpRVTvJ7eSyQb849E6Lf6uLQ///+7f4C7s+XBeF619Y79L68KCL14c3RfFqixeD5nVinlr8bYqCHwUXoAriT6MjTF+wjB6MGyIO5iDWgvzE3eyvcCiajkNRIQ9FebAzqi6S4SBw8YC9GcbmfuakNEja5QwmFRelwjPqjzk1ZohWS6IVK2gtNNM6UQ204kyIy5PE5MEJJb40TMhXCSW+VBwEOB9vtaV+LUTNigkj6qlE/tYvw4g6H8mXOlUYu1V0VXkcV2Eq7A5wcC3NzEgGF/KzHJA4O0bNXvieTi9acZz+pdhV3wb/GA+A4xwWcTq0F5IovAS8M5iLOGa6Am7j0jdoA5y7d0nUTQ5kjB5NlOH6XBWQrRh5OFbuXzLpiVE/FzvFQ6GflcUpn6YywVVSlZeuMiKKH05UBlfgC+lJkUCuVs1eUZXN0T6O02mUFnSvQn6k4HIefgsdht9lURRcih6SOMi0NrWVfvEDg+0qJgGm5uWyL7aQZXmBsN0RpdVD6WvQtpkyjmEUDa03NRND67qo//6hVXsvtfyHyn/We6l0/4Xo0Vya/Vr4+wVUtDsVNSoPcalQfA4d37R9lbbuQx44XmmN//aXSvv3GW8l8CD0tTENuO/gF/5fhMoY/x7ZJxxfhrFPLKA13tUBtk9czaNN/KfCPpGD3TTXbJ/4BHpxrTbkVO1dZKOFyWZxkacxNouw8uYJ+/cxknfKuySvF+wyevC1PsIeQ6PrrM9Y3jyWtwucIcpAAVkyRKcudY7xJdqRcPjAFB7U2bzOsXpT+c0cqh02yNMotIyjCeFjJ7Qie89DUcaIUCoQwjHkJMQGCFtfHjf6P36v5m/vjwlq/j4SpVlz1LStFrVqImEzCs/0+rye6sZ5fSKOf/jTOPczMdlNbiID+1Io34KWXGCuOxiQ9kxqnzcNnv2u4fZZCFvH6hlRGOYDYVMAtmZNstct6pym0Pn9EMlQQrJaIGluRjIEkCi5qrvj/Iyw5W1KysHIRJPjBIADhkfsIP3J9muh384l1IME6gwz6vc/BP4Oy/d2srE2V9GekP4NYdnHtRW/JKkJVV6a+FyqYjP43WJZglqT7caFv2m+OSLeU4a5BUj50CJUS0Gki9hkUcCN/8jITtkkVW4VSnWjWapmKBXZe5YIRCgYshl/yeFg1JTZf4PKUg26sQkGf/MujKEFIK08LqXKPVFJ5xlQgUbKT6It8pFXBp4GwDA1l8pIf9mAWNyzm+PCsHYvAxk2JUKZTSrWLiQ=
*/