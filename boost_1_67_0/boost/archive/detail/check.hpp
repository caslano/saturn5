#ifndef BOOST_ARCHIVE_DETAIL_CHECK_HPP
#define BOOST_ARCHIVE_DETAIL_CHECK_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#pragma inline_depth(511)
#pragma inline_recursion(on)
#endif

#if defined(__MWERKS__)
#pragma inline_depth(511)
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// check.hpp: interface for serialization system.

// (C) Copyright 2009 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_const.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/serialization/static_warning.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/wrapper.hpp>

namespace boost {
namespace archive {
namespace detail {

// checks for objects

template<class T>
inline void check_object_level(){
    typedef
        typename mpl::greater_equal<
            serialization::implementation_level< T >,
            mpl::int_<serialization::primitive_type>
        >::type typex;

    // trap attempts to serialize objects marked
    // not_serializable
    BOOST_STATIC_ASSERT(typex::value);
}

template<class T>
inline void check_object_versioning(){
    typedef
        typename mpl::or_<
            typename mpl::greater<
                serialization::implementation_level< T >,
                mpl::int_<serialization::object_serializable>
            >,
            typename mpl::equal_to<
                serialization::version< T >,
                mpl::int_<0>
            >
        > typex;
    // trap attempts to serialize with objects that don't
    // save class information in the archive with versioning.
    BOOST_STATIC_ASSERT(typex::value);
}

template<class T>
inline void check_object_tracking(){
    // presume it has already been determined that
    // T is not a const
    BOOST_STATIC_ASSERT(! boost::is_const< T >::value);
    typedef typename mpl::equal_to<
        serialization::tracking_level< T >,
        mpl::int_<serialization::track_never>
    >::type typex;
    // saving an non-const object of a type not marked "track_never)

    // may be an indicator of an error usage of the
    // serialization library and should be double checked.
    // See documentation on object tracking.  Also, see the
    // "rationale" section of the documenation
    // for motivation for this checking.

    BOOST_STATIC_WARNING(typex::value);
}

// checks for pointers

template<class T>
inline void check_pointer_level(){
    // we should only invoke this once we KNOW that T
    // has been used as a pointer!!
    typedef
        typename mpl::or_<
            typename mpl::greater<
                serialization::implementation_level< T >,
                mpl::int_<serialization::object_serializable>
            >,
            typename mpl::not_<
                typename mpl::equal_to<
                    serialization::tracking_level< T >,
                    mpl::int_<serialization::track_selectively>
                >
            >
        > typex;
    // Address the following when serializing to a pointer:

    // a) This type doesn't save class information in the
    // archive. That is, the serialization trait implementation
    // level <= object_serializable.
    // b) Tracking for this type is set to "track selectively"

    // in this case, indication that an object is tracked is
    // not stored in the archive itself - see level == object_serializable
    // but rather the existence of the operation ar >> T * is used to
    // infer that an object of this type should be tracked.  So, if
    // you save via a pointer but don't load via a pointer the operation
    // will fail on load without given any valid reason for the failure.

    // So if your program traps here, consider changing the
    // tracking or implementation level traits - or not
    // serializing via a pointer.
    BOOST_STATIC_WARNING(typex::value);
}

template<class T>
void inline check_pointer_tracking(){
    typedef typename mpl::greater<
        serialization::tracking_level< T >,
        mpl::int_<serialization::track_never>
    >::type typex;
    // serializing an object of a type marked "track_never" through a pointer
    // could result in creating more objects than were saved!
    BOOST_STATIC_WARNING(typex::value);
}

template<class T>
inline void check_const_loading(){
    typedef
        typename mpl::or_<
            typename boost::serialization::is_wrapper< T >,
            typename mpl::not_<
                typename boost::is_const< T >
            >
        >::type typex;
    // cannot load data into a "const" object unless it's a
    // wrapper around some other non-const object.
    BOOST_STATIC_ASSERT(typex::value);
}

} // detail
} // archive
} // boost

#endif // BOOST_ARCHIVE_DETAIL_CHECK_HPP

/* check.hpp
u+8xS3H9qSbMi7+e3n0YxCu3/KfaMvzIVK50j8XOD5ahhZ1jvZK6XCyOGQAbP7FZVzyyEVXA27wdv2lahikrCHxB3wbxHaeclSROH1eCcrrex3P8+9ihHbtzDMP3RgWRvZtKTnOoatDCdLL86XMKAl7ziOgN8cMJuqcOz+jqHIjO+imeGl1DQgPerF7XVLWfn80q48X9wYE01jHXa+rqPtd4iQNoeGWAnKTZpzX0ALmitndjN4E8dqcxlqgm+9PvaKvWr8bcUYrSECyW2xiH+S6cnAll+CQkPOZXF15m3sY6x8k8sB6V53b1AiUBjTLTHCnjwbyKsDkqqX8MkcOP/Y742whR5FTRGUlnm9s36s7Zj95K9dNQtcIRQAyAOYgAMQAW4DyEvxgAC1A+4v+MfrFYgOC+8sLbEL5R7B4qgkGO5g5p5YQyODjiDJ2JfqOsozRQpeKQl2rqwVpaSDPiO6911dR8HYeRQsaRrVOnRmivmsv/rRP1yyrM0VfVP4mUcTAk+0m1YsTb5YVVMbrgOkj9eZ6kPIHYcdmQKGXMBbW7NI13G3KudMbUcH17isXV6ZIe6CS5F35GYI5i535Kd2IdfgjqK10O/CyRuaAPP2EPINZAShwcyzF7k8Phb5trZK1dGWhkeMsHvc3WzCnbkDcq+cRfuMTZv728pXu33GG8E9D5oEyPGx/3gg3Qxo17dhGY9u3AjjnMdwjsgBxOMl02Vrh98FyKQg9TPsboC/x06wajuCAjZtgRIExO6xUPF1FRKiQuCy957uw+ixlGttZ0qfxXBS4jXpnb91edAnKQ2SITH7/5eoU+YI58TmVICtVD748KX0afWz1cOAwX1u3LtucIzAJle7mlKLl7rVxzFJNSedhNgzydiYY05Yvu7mJIQKT8OHg791eBK3us1FJyy1NSvhdEF5F3t/GDaMDgon07trVoEN+FocGCQQhIfNPiBb4jMtDcLSjTG1GksEL9DxGoqNxRhDBJgcULGBR4YAqi/amgKMr73fQQ2rx2DRjtOfCigiWPXPGRw5RHJ6QkDUyS/wgID4YBDAOY/TXymPzX57vGLprmWMlOexGQHGAIduVfSKsxBIDEfYmXhKAQkP4a4uN/ZAkNKPBdDpVjIgSprUzT/73vYnikUbKe7m5mTt+AO+meqA54zZ12ejEzIGbUOTNe6yBxdzc0tzp7ch8Lv7wuwlHciwq/3xdNumpKtR0ZTxSAWKBTb4G8LDVFJaiPn2mMLPbvWft6fWA8YM5Ix3wSvG+LRSPxi+fsqSZIZqpLfeWT252xq52fVVdFilogNYDBssO5OHFIRSURiCLxye+L4uopf6ac6ZLAShTrhnLhI7lFtuH7URPneUuf9qJmZDJLo7I72lIUnunEUByJ7UX0pLXqgJENLIt2ohhaTU8QlvyTq5tAj2CelSzUZg3+F/6lKwbLoAchng1B4nirKKjymxyMOvyQAWlSwFuwZJ9VnvuHN4JWXejtXqtmML7Namp6pejnNMRk5BMixWClu9esghCGW5i8NBKDEEHNJORtLp9hvtTFSSIl1Fxt5orceQznPHuQfmySDWlxK0USk0w7J53MePD80UxoVMgYJ52EQPecirS4q/u0ItUvjEzokBLrfj4iMvGKLHmQNCMZSSUqH08dHbJLu69NZXmi221wduUPuoD9RJnUXhgfzi0LZ5opImN7kFGM7e6DftdsdS30Bj6zyXkcPbLJdq1SjfwyRMX1rbjgVADloSyMQ0vWEGe+1MrOajATw8rjcBDUywYvbJcJN1zsSOC069BmONGQg7kvY9yMnPb2pejJ6xN8xw26d6dmC3dXvZDmiWSW2M3cvrsalUs7ypVktjOqgNuzInQbwYAyIPhyAk7oIcnfOpAijdTs+HXhYrOGLk5Wj+Us9zsRxX2GstXZ2dRtaOVD492NBsdvBHnvFzrPwQtnlEVnfR1KwpNbjpWqwfuqMeBZVJ3h1MrbnVFyPWkaXfSg3JRqY58cYQJsTLBWPtYeoDbFqrlo3v3z/Yih6L4f3FNRcWqz2FFVE0nUHPIb+jEVvEx4oC3SqUZMnLuQwUFv61HmfiZQSu6kJKZdrN47ETz7wa0rftT267rICNGJuAOD/pgocd5o1Yy8pkO3tOZwPca9vRrkHsF34d6RrRffiFH/zSJtWzNIjNwQJ0zzXpzbLRg+2d1jBu4SPduLZUUwZy2BxWGDHpfBBd/kUtzZ59mrJsHmNjn6zHn6KqceEu0Snlsl5XltQ5PDiJVZSFunjJx5gvAh5kzrXW8ENoGXNMm7b54tTgSH12B+/zE5125nx5fpVzJHdXqzpgn3bsr3xmAJJJpWfIksVxdzIH/+GqHQZk2oGEd5UhJqPy/yJmJDiYYG2pY9Z5E469k15r3aHaqdv2bLIh3blU3S6nZibaLl6dL0NxC9TAgOF2MQdgthUEtVJzL7iwJHDphq7HYdtpUDxfQ4phfzKSC7N1Ivkyq+S3OPfolJtkWg2vcHgndZx79ad58bTc8mU25jSoRRXQsO8si2PiwlX4CLiv6IP1OblvkIytEqU9n7MvHIZCr0cNYUH3O8dQhSsrtM3xtsI1gHu9glhXfpdQdfHnl/XUqPW14RXX0pr7dkdXexxMc0lW6xYXmK2H5+K7SMbxBJ6eihZOuqt4JhrIupLbZNABaKWfXSqPL2mWKS3CEJtjCBl9d1Cdp4AERipxGkBPpbMOUBSPeqdGYMrQ9kATlEjHs/jNaw2olsz86XACnYZt/exzolVWU7SMEuHzJVEZOZsB1geAX7n2/EcM9H16l8WdEmrPshkFEueMwqmbkh9Sy7h5AoK7LH2RToSeDVV/FTGfDpPTOpGtPtEG68lEJ0ZefKCgdWyPo3fdqC+VjDuXs06N0zNji7SDpqxa/QlS18ifiawh5/JRWYOnaMRJ4B5xwp3RBNAO+uTOVQd1F6wZZ/DhhSmtK+/PJkPtRq2GKaANgZC7UiWnx3uTPC6RHVjE5yK3OSXOBsCO/URpcDW0Fbf8RaXZafPZHSypHzXb+yaPAbWvpkw5NWrNZ2zJsAWLZNjJ8bPSu0gzRSiOe5XnjDFuJBZcUs3OKCtilkp8U+gk2+w+gCa70wT1cOtU4sZljRngsQoTAD230qidukoMaBfHRUFnint64shFKtk82R+uJpzRDolH20TXbDMONqOUJ/JDw/rdbq5maMrf7I5jSx7qEsIAtgCaSA7J8JsAySTwbAClgO+T8jP0RWwpe1jfqxvr3AvnadTyZ3I7ehQF/PHhDeCQ+ooeIrJEHfz6ZIpKsoauJkvXbIAgW9w6FD5QjDWh5qiMVIZZ1dRdek+4T04ncNrYj+5a6gtjYsrRler8ytGepOrb0tyULcildO0ybXWtAF+Ug1BLCN5sDGH0YHtt0dN35POr23q6+XiRWfYQyfjt2ulMoW0mimGcxuOXcnwUhJgeoaXfOHCpxX0o3kuKEAQVnsOVIXxn9I0ldBd20uRUtIueI1NrTtt8WsLr0rNo+vLuBuOtwJpJ1cPLa7fHYkyQmfuwP56b7erNdSQc0ZlesdlYmLuUL0P0cLoIbaMayLbe8qDX1sq9v/GccdnulCGA+cFfAHkS+56E153djsQpvRiO4obtx3fYp1a8Ku21ISXWbNV6U4dbFcE+Uu282Q3cKDDE7hdfHB6BeWJ/sRsmw92QS2xTd7YOG5XYvaFpJi5Hn5FpqUQCC9UkSlnnp53U+HenBtmSXdnpDXPUTHrmK3uo0HH77Dzps+nE2aOq8jX3P/DIDp4Tsm5Ht+xjRg6CBiBSYMEry4MKJ8ewy0kBDBBgUaMNCRgwaJ4kJ/IDTgMYqieg1NTBxtNCjxg3t3Dt83dKDYpAQhKco/RVXSb0wBmkoYglUiMISs2VuDf58dlSBD6KZEcYDDWkMAh+SM/iD9f7sy/fF/f6aH+Eh853Y9Wv/P4DYHkid5629sLFPFtZZ2VG2D6QujsU74tcT+Zoql1XojUYloIpNUaM1Xkim1oQR0I2w8kTQSIoGX6pK9yPbf7c2vXt+X147njx7DU7TTrNPptDf/mSbf3VP2mR+rKRAQ4N9NNRJTg5ciS+Nb5dVlhzfqckDUP4i6RVz1VMhairf3I7flOWPQ2YQlWIxo+Z7TavwNRSx3ivv4I6/+LYYpq9Tlt3hPZZsoY2IzqskWD1phBE2sSULMR+gqLw7W2RBMVJz9lCUqNEQbPVbq1knu9GCPs76uLx3X1t9hrUc065h69UdFyD2vxoLwD6W+90D1xwA2OcHqWPn7DcVcwnBv2LGrATewS9ef2kF+AcbwtYghrpDS1nQd0MBbWvcvqyt4C67Vbo3Z+R5MibAs73s40mZqkqosWrJBOXBZXtkBVckLniaAgJCb1oi4rxSj8J9qXKEt6tiTtcMkkNf7SJEw6z2cWB4YoHjncSFVDfilHRGbUZZ/8BWyT/lY9yc4CqZ6Azs1o8FR53yZjueLp7d/MyoScycEq5zbH4igPk0nJ05M6o+m+92zb+SexL5NowKkDvIvs7D0LZAhMXYU0Ejp+H2e+/tczM/jhRgE4fhDOVeulUgci5dm43eA2CvKkHLOs+y2Uq13rExatewHqp4HJM1m1f3D6SwxADnotRMdx/8k/WIprXlIFSdkpot7UvRRg2K/SxiyCd83nkfGd2dftZLWDIkCyz3ijh1Jktdz3NHYuGmWNLWxkiuWwLNAHLHE1Vx3uzjckzjNFAjpXx7vziDayknza9C3OqGMcIMZZibMzvKtpKFxuxXLPOT7tvIPeXsaOsmqWgsZmAQ/yDKYoClKIlAhfH37X5vfpT2+2HR0LbBNNbvmS3o9MSN2Cx1VhLB47bzwMSud8ot7G5TWiJqHkOH1XHp5uN0WO4hzvSXSA6T3hCiWfOwk/DW/SZDRL6Vm6vsvfcJGSivgrGMtk62aYurnrgnl1RXL+LB0CcXJX3EEyzArIJcCGISUxEUmxWp1Wn1seeNUe+9/jc1bs9jsfuoB14Rt7CXCcdISpUsYfNjL6F9JQoe+1rWauJTvCpHJm8eI8yqdHaVc9HzYFGftF/aVBiz4fAOg2Suy1Z7RjFiuwrIhUJFPB4DY4V6PcJrjRzkrUsrOj861P+3dgnnGFK/FlTO6JlnSsqV1WtzBG0sLnX/CxDuuSHTalXjd0vVR4ImJqD89gieP0jjlkQ7p8oKs5lBJ4Lmwlu1LPNM7gqimYaiUIOUvye8jWZa7G+RMvd6yoGC3/ViNcdQPfZCqnEC/F9sK46vT++wK8hh9c7P2hUqymzdTiyTaFTW1MWiPdrfe9R9bOTvlFikDVOHEw/VXDY8gMgrRs06SQz8LJo+mjnmNOYYbKYdaoFmzPiqrUHM8VvQymqUEUvavTZTo1NSVNl4/N1S+zuv3e8jN6vuDUzP0MY3Rqj6E73uly2jiLGQg0Lz4rAHTrnv3bBCtjiv+EXSTedmi0j/i2HV2v82mx7BKcwyROhWsKHxlAIPfoR+GDpEzwaeqlIqG0JNKyME85OJQjR15uW8KQwcHQyvliTeqBV92J8y5w/I1vKaa2a+vQ9cgENQzcS1ClFR29Z6eo2iZW2ZQ1MUL8gtnKSxSae2dHfG9DpdVlwhWJoyxuj7fe0ux9mpfZCaIyzc6Dni/gy0qEVzZVNeRLmWfnlM+00bUczsJtR8Me97VJKsWgOZxB0aVzdNwvalhr53JhTlqFf8Ms+A3ij4Rav3fwE8+KG5N/G0T3Bdz34b4yza4J/a+BeGHfWD3/4N+AfeE/+/Fn91/B81fnnGkjztiaYjvPALpibp4UowX2kYRX6FUAgoRUSXM0nwiyECEPMFEhXQoFCgxIkJ9SQ4ZSVE0dwlJQdDaaoAQYgQqCAwNTFBl/3IBhchJimQmJSQYMW90TSLEPeFUr9Z4UlbyhwVogiJVsPgbTyACIwXg+AYxG8Mp+fFEYTyB0Q4IgqPJb7xakcD4+zxI9cAAheW/b6Q7+JRfJ23IJJFf3JpochTXINe8PrDsKDSgwK9us8uvjxObQZghiDjNj+59FNW23SRpu3xeDvtXl9CJylR15dH0KfkFF5CAuduZIf7nPVG/mRSDY5+K0iygvkKOo4HG3X/7gUEG7YWwZ8ZzjF5XrQ1Yeo1v0UqtWOrbNjIuUZ3UQobvIUua0zxN/mcOl8xKYzVVytmmSOXU57s36YxqHJb5PcMqFOVdf2LcOwlbsR2WKj4GPCa7FxYzrGFfpyZA3+nAPmnk3PJdfKz95FoRmSQj6bWQmkkOxyHkmY+K8y5tBVpU1IUxQUfbOBRH2qmWvktiXs9k8GRlptooHk265tjHoaYKylsGrX4uY1DdHa8E4rNXZHBWW9o2MuZkfC590/Gko31tf8H8cxeQKC2zl5qs5O/l7XWHvc/pAWSbiOiOBMU7HSz1VRv8b72OXIKXweG6ZZSnIc0bTkfiGuRUar1D8MCNrFTkTfmiHGo2FUwj2jKVHrdO9hY2XnYteaJjRWF3cQi372/Tb3Qw9DOk57F0kXhQ9qM7+PjDXdu5sng+Heh7/Qvn/f/6zmqKGTCCxfPDsHFihu8R66plbcNwIoR4zIw7cTcs69VUGoBT1FRlyS1AvP/Ysg+PM+Pvn0Q6PyuVxv3nrNlE7csGGdwoGeIPZ+iwO/5yz8qRXGRllED99Fn+WA8EfYh48trhjKOuBNogZtPQrQdbEeC/ubXFFzaXcpeVIIF9joY+Swuh8DSszGiFD3eXllI1NjdXopKvLF4NpszpCg6lrsE01KNBNmPXB+p1fQ8vkTZX6V6H5z4s9GQv9Qggh47EajWU8j6MCMZN24hXWlfi/aYeQ4f4N3D3+V0fFZbjAGS+AAf3Zn1A8t+3DUsKyYq2M7/C3Yfh3r1viaWoxBhY84CQmaH7fvO2USq9eG847MrRP6QkeEfZlU5bJPLhmCprI6f7ZsE8pWPMeHVt/1ZGy+IAWVc5Yg0CygVi9sz9o4WrH2EegVCJzPzNlref2e7UhkvJdk48AjdRuLWcYsSVQleSd79mGx/+eBmTHeR///1+G8k7YYO4kB5MLDO6hQZkodvdXgS9QWlwlsAskXorD5+NQ+bNuPFrJ6bW9gXboJZjpvgpY8VYn3PAW7zx10mOo0Zpwxal3ybiHySaWIjKNkkRKEWWhIFe1BVRAmWvwXjt/8O3bTXuoZjwMcXitcKJOHA3zSLRzwAuVN5nPEWFsCyckrriZDvILY2MDOlrAOUxwvmLGoyrerPnZb/7MVwgx9p7/Hgfx4+A0rcfzgv/BL9Id49/XPmZCT/LPVZBYcEXL0LS8/O1lGp8xsjQIFid9tYH9eV1205T8u2R+ySdgUSt1kN7Y5nhYcw5Ce0hIVvwVZJG2ZE7Y1Q+CrhxlNgJuxkc5nmKMTDeDqLXiYfSQ7HvcJDgNvoZ1GLmVEvIkkWEhIVgfqU0o/5I9qjyioaxy4FTNzebls0pHEtrBZPH905b39BUW/TUJf6We2UavyRcEsgqRdbo9g/ljHHYu5fL+jcw4GVoupymA+IwS6dNBuVhrhVBDhx+6PTZUCd/N08bI24MrVPpEISrdUxeqxpHb4DVjh2c2S/O9G5yYGhrDPakT2poqz2zkhnu09OlRUn2EQiuFCf3lMVPO6a3InKVaWeui/H2EnTmcRuL4LSX4Fx7kwt8Ct45LECB9PpEcS2vwKMoYlxMSwoP7AAt9StKh8lJnB4YEbfx70DahNaYzRlgA8qG0ztrkmfDDM0wdmzzVjaoNKxePuu98qJtVYpUgwELDRUzIqJh5E1Dlne68MC81bjW0WNgyNnLr0ktxuamACViXfBv9Mm70YPJYWBHs+5ZM2SBuQRXzE6G8QOb4QR1anqHAAAYYYgrGTuS2Y6y3/kf1Kl8nLFZex+C2W69ntdskNUxWStjOBApOn1VaCrzR329OZy9ZrVQn8cJSF8npBKdC0e5oRRI/g9kDp01PJ93Lf6F60CbKew3ZitHFuGfNlwyAFSlrCCEra1DOb86yMaYBXCB5zTULYLPL71JQ7MdoxlJEkG7e5+3Y0XAO9fOcCuGr1JzJvzPmKP1zgig1e5fVPrBtXGJ7K1DipqahV/lwnZtXJwyo246C+KTiGjfwrVv3Y9F82kFi0BCyCp5de/GU3Mbz+r11lAd8WiUrLygo6pnredz1BTZgCD9lEoerVWtnf2x8YlJFD9Bf0hzsI5wabCq0Qv+U9VY4Xtix0rO+ZVw5Cp8cmpqYmVBIwIcQd+ET9ZRjmdQhKbbVyFVsQnHGHkA44y76OB1GjahtVsWx3ivdtzT4WOTyMctcUeg6jImK0XB7DplTipgDnHKAn6qm4pBn1szf9e201DeVrQcT7NbU6T3gXcMI73p0HvohI9HIaS1NcyAksebpTVdfO7g6OxHO/VxV8+Siwyin6y3It/szYszLzOTKJ2t+m2tW6fhdAGLFP/jY6VNi23VS14V6qvdjZVBeZ54zbV/nbwUwDJ+Lc2hGYFlfHYw5jjfFrRygiIzEyL8yTOhXsxzuteH7S1kA8z9o1xXxMA2tvDs4cm351QLewdwyR5w/h0gmLbFxAnfyHtG8ajcJsBbQwLk+ShfMcy2y+xuCRJWykAjW6uAlLCULD3UGy8L2zSK7Bkih3nX4qW6vY9eMHSVD/Qx2xEFCV29o+m6ZDHnkvbI8JGSQf1dyWQ5X0bxkPsS6g0P0yR1JkB/LV4FjRSZFSOAwKA9VyYgrjYIwDLG8dTfRYzmwd+qPg3C4xkkN/Z+FqP6cnF+E4N3ipT1CLqBb7y2GQzAd6KfUI5Y/SsFgH7CGjBJ6DaUwGmelbupVUne+HuYf6/f6zG3vtVIriuZmDg1X/KP96TInHt402MAR8wYauN5k6iSNbxXTC25ePp8eH1wCSaWRJBfDwLtyT3HMKryr5LIdkD2K+vH71lNofW/J2Qh11xbDtMIq0zBk/7nLkZxXwd7feZYP8sROVTw+VdlJSGLNTn+QMjrxfoY6U3KQaE9MWnsFTPq567a95nW3q/NCVEDVS8YEfOPGNdIV25cLQj+fV65aZR4BUywCZ16ojGRpeaZO+uXjbNpv5V16vmW8G0sSAfkU++CiKh1t/AkIAR+6uQ3na/fOh4C0ubGgLyytB7oCWzy1KWH+qa3/k5D/zB9ChAYQPFyAgMIFKRQkQCBRqTPVww=
*/