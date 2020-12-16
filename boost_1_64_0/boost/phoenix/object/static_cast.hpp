/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_STATIC_CAST_HPP
#define BOOST_PHOENIX_OBJECT_STATIC_CAST_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/proto/transform/lazy.hpp>
    
BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(static_cast_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    struct static_cast_eval
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Target, typename Source, typename Context>
        struct result<This(Target, Source, Context)>
            : detail::result_of::target<Target>
        {};

        template <typename Target, typename Source, typename Context>
        typename detail::result_of::target<Target>::type
        operator()(Target, Source const& u, Context const& ctx) const
        {
            return static_cast<
                    typename detail::result_of::target<Target>::type
                >(boost::phoenix::eval(u, ctx));
        }
    };

    template <typename Dummy>
    struct default_actions::when<rule::static_cast_, Dummy>
        : call<static_cast_eval, Dummy>
    {};

    template <typename T, typename U>
    inline
    typename expression::static_cast_<detail::target<T>, U>::type const
    static_cast_(U const& u)
    {
        return
            expression::
                static_cast_<detail::target<T>, U>::
                    make(detail::target<T>(), u);
    }
}}

#endif

/* static_cast.hpp
XNT7GVXn5295mmad4S2O3WQUBkeh9NAVewvei4EEGLgOxD6qAraMpim//HNO+2fMRXUluXfGUmaji/qm+guLDee3uNf60/Wz9fZ1bJhcz9qR0OLGIJsm1s+7cnp2A45Mat0LY5OxJxUS2M+gavCC1jyUX6eWX6fcQbsIIdbq9+wsYS8/P0VyXkSdkJ9zxWN9qMjLeKHsORo/haxGT5zI0WGMv19h/HnseZQTQpb1G0+ELP5D6SF7og5N0pFGyqh0o1nZ2buWVwLcIxXaXW0UIp1z9M9wdUMyT2njPSuo2+rMedx7sK3XMCkYvKBXUZvh9/W4Wq2yqCMXYsOe0vQ98dRjFhoGXFQrVDUj7/xC1NnvA2ydoew0DDDyBKCosIEY4oyH5xtezsPzN/LYYOC9AYNN4IryjfRlKd9EX5Hla/FFBF1QfTMvqjynKK9YlLfiospT659lPEv9B0dT/aeH/57XgXr1V7yqNV+N5qvTfPWKD5dG2E/dkT1eH7np2Ynz8AsDHIHRy0cZIywrPOwJVHEPT+OD1AUT1GVTspfxa7+myvrzw8nCWuya2NCmmLAW664tX03ejCHBA+IHwoiUXeRKi+O8HPTXxCj7KENQYHp+4ryrqKMkiunAbMZvUU96KmjbexeRwVZmScLK7PkYvclYyT4uhNyzG4613aoajg3SQeA3Wo6ojIsVfp6wlJHPU0bMx68tqBC9WFD2shVW5RbFCqtceDwAIyrIJRMzExPOrWcteZbnGknwPQGfunY9IPYSS3Xbi1VM1TQ+IZhYWbJXKZnNlhBq3BjP8QiRiF9m47LJpd+QL4VOEKH8RR3sr9FO1JajtIx22LGu/eXLYql9H6DUhTGRYlCIdD7YjF1hSS2LErs4cI71lNWQl0UR85++h7bTWHrqm/JofHXb40FCCD6CgctNAqtnVYuFdOhTVqthwJUjPwmRUgXnsO3xepMkpgC4tExGgTliqCWCq76DUb8leYoZtX9toy4hBJ+mcOwRPSQ9M3FewXTuHfFnr2nkJdRU4PesKlkY1JI4ATez/HMQx+ebFWL7/Ldw1V4zyZvVz33CYC3+FUWGLPmmbFaEbcxmnclfyXFudXKNrh7coyrY8PHGzYpIygxArmExxFtWGdJP5IpyWUSkmSI7isjosEg1l+pvonkUUxlfSQMiVJtDSxjzmcU0/WWPaAt0e6t7VgQv+oQlpEhc5SOe4XBD6K7lYCHnFbk8y8soPJ0T00ibLo+UsDWt/vjMxSAR2uxnigWUxfUgqwWZ352YyVPCfkITAi+e83bFi3MCEecpqQIm4kiVUs+iXeSjna9FvcLIeNNoOCcdgf5hv43DkMWcUqqvD4tvI8GiQFgOT7Gv4QxC4dmMjbOFEvHzTfUaPz2rIm3fI+TjUGiwiF+BLmv6ngK2CDS8BoLuFo/osw0rvOkobESHKkX4lkeSnIhT4eK7VaOIZHu7CFZSirko66kvXxR6ageSArlqmy+PJEpyp5eJYHECUZCj0ryqBdUgT/7dURZDJZOaKuqHylAedXsWT12b0OSLFNXtdDkM4WVF+OTGfI7YrZboW9WCKsTqWNeLTcGDqmnqD1AqIWoZYcnJMB5SnAIRJime5Qm2UJJKlIiE4Md/z51bjHqNS5CblOB34pDRYSCrB9FZG5nTtgoe0oxgbzVe2JTCiiuE6nhGIkycdBaonJzpMDRXrYjlCfom9BUnEDXnMO6lw6XGTUIlKAg8Ap8eotnfiBJiX9YgfhEsHLzxT4qJti4RsEatyyAc1p8orJ5g9dGfYEVq4sJZ5Mhmf0OqiR4Lb0V3RWR4E/Lo3Nu9ixumoIN9bET4yL71BdFjeEZRwo2+RAo=
*/