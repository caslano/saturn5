// Boost.Geometry

// Copyright (c) 2019-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_IO_SPHERICAL_HPP
#define BOOST_GEOMETRY_STRATEGIES_IO_SPHERICAL_HPP


#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/io/services.hpp>

#include <boost/geometry/strategies/spherical/point_order.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/point_in_poly_winding.hpp>


namespace boost { namespace geometry
{

namespace strategies { namespace io
{

template <typename CalculationType = void>
class spherical
    : public strategies::detail::spherical_base<void>
{
public:
    static auto point_order()
    {
        return strategy::point_order::spherical<CalculationType>();
    }

    template <typename Geometry1, typename Geometry2>
    static auto relate(Geometry1 const&, Geometry2 const&,
                       std::enable_if_t
                            <
                                util::is_pointlike<Geometry1>::value
                             && util::is_pointlike<Geometry2>::value
                            > * = nullptr)
    {
        return strategy::within::spherical_point_point();
    }

    template <typename Geometry1, typename Geometry2>
    static auto relate(Geometry1 const&, Geometry2 const&,
                       std::enable_if_t
                            <
                                util::is_pointlike<Geometry1>::value
                             && ( util::is_linear<Geometry2>::value
                               || util::is_polygonal<Geometry2>::value )
                            > * = nullptr)
    {
        return strategy::within::spherical_winding<void, void, CalculationType>();
    }
};

namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, spherical_tag>
{
    typedef spherical<> type;
};

template <typename Geometry>
struct default_strategy<Geometry, spherical_equatorial_tag>
{
    typedef spherical<> type;
};

template <typename Geometry>
struct default_strategy<Geometry, spherical_polar_tag>
{
    typedef spherical<> type;
};

} // namespace services

}} // namespace strategies::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_IO_SPHERICAL_HPP

/* spherical.hpp
26BbSSdwzE32Q/LXzbP1h1MD6+zVIJEnrwUeHQZMygE8lPe/nbzCbRVc36VRNln6Xswtrn6l2ZqGijJQogcoKuQB3tSzAHD26Yl3muZ1kSLdLAwEDdGT99cBjCibavDLVqWIEh4sAJbmCB8OIsM6Bd7y/QfD3BouAkE+SYLqk4380PLtyfqq6tbanmtv5oj78zXV2ZvBvm8TP0H70mOGDZZve0VT/Cq3S/DwFG21G47NSGFDquPIC1zxTP2Sei0jYWtjlYpeua3iF+V5atSNjeNFRKvF8iyiJrLV+qFoDtGftD9sPqyPllX4R/vJCaREg01B0jBPwjXyIMwogVZ710Mkwldc1204rmCXdMi5gprXneqPjCtaTxQsYnxtAUwGQbDwjGXsOuehWQziw/oFrNWrkaOj75Ic6+HQFgyr1NNCzKiT+UVzB2E1zuy9jD1Tm4W36+wlbNMf++nDNhvb6EN6KtP6Wn19zuxx7Dsb4SHGws4SokXx5qzVVSJzC3Ux9aBRbd62pTNFZTom35eu+jg7jnh+TgKyszpNlSmTqfNKb9E2VoxyQo6Af8uTiCePmqvC7FDjoKmv+vRxs889gL2+gB3amBcMNP97SMxj7oYlklJ0rXKRQqPJi9RhrOkSREOVELtKemh3yb4afkDsAttPoYkjpmvURDOW+CfRCrF77xUVHOmfMTD1C8KrCTi0f23DBEMcAbRqP33mRNMkgHo/GDUX3orBS7fqFuelkyBj4ltDR0LVtYfy0/tSxYtOV3n1QRJMrmgPAQ+5x8ZzyZdIWQRbHaDlcS8Ve9tZHInei+nw8RvVPEYbAKxFF99zTKOB2142nihuPGrPlXdV3mvL93cU9TJ/ju+QNczGuTjelpMez5ky27ea3I7OHldsULuc1t+tSaMkGzvqLZ1OmjIhM4bchnbeGB22pbyx46yNPCJX3NPXvRxfcrzPw2Cp7nFvM5nbp5Kat9brfLJyndbn/VATMVavB3vVrS087fqbMc/vvLOOqxqezz1FKl1tlTrHy/6v+YYpDjY8go8fn+v0VLxRz83bp+ljMrruYuKf5/YZMCxVXt5n5YnU5eT90c7kra6lm5ef4rL7trTYbeeprmC8yjkU60ZvHxXNNzRVXhezsxpc3yuGgqLnnYIZbRJfl+W0m66khfrzbkdP2tRu7Ji1GGzzC+tWy7dstpuvoWsOIn+mmY8Ff3dVap+Kw/iak2VfJ73hbKnonZ/DsqOVQzWnVG4r6nYyhxNTLOyW7c+tmu69G43GQbuxTLScVYpPl1VfnzUZOa/MroqC3NKnt5RptnaRujcyIhC6VMx16AmbnT61Ty50ofaQ117YrRa9/Z+ofuwPTThz86gyY/Ctt+9+6bSGwh3wU/5DBYZ3ftRW4qfbR9C4o+KQkKaRsM0mTZfuTyvTye6S0vLVpi7fjz6sCN45eLCuj6mbdd725oeVN13e1/fqrpuj7cdjlKGUCxNdZ035GefkyHXRaW1lb6afnR6v2u7LN9eeWJTpDY++ds/qLee/Xm3fvVJM6ytb9da3S9E7Ng9XfKcfC6Ziaxsn290/775e+KuaTbk/Wd7RRzk9dDoOxd531yKqeDrbluovNlN5gXh06T8f3c2aN5Pu5/6EF+0pYjPbnvpvIDHPbMeq6T8Fl2vFv6Niy42580Q3Z+1n3WJj+Gpigy6j4yQmIP3NVne9y/rueXNnMq611/WKqAjLd+01KS/XY2+Dimva+wvNtMtt5gvrh6S9ZrHTdnqB7+dse9faNtgSrvGyyfp9tFl9s01+mwpz4/siQASM2uBDqG7lBE1lS7Xxgu+H/UJqvutZg1MEeEftgDFvZPGFkexhGU93eCNYd2OMd0HKOPYspVMpJRODCx0Ktg00QN453dKKOQJJa8PTQ1tIL8yLNWOtal+tOS6OhDOFOnP0Wmb/y4/eGDUrOA7PDrcFyLNNrWTS1O4M+VxrPNKd9oCH50ursOC2AEiWJ+1HMYAJ8jQi65DFWX4cwA0NCaQmfiJs19kIfUdmShUV5CuPvM3siJivGvls3MkplVGO4O1uzhAR8OZFUkND5RgdGe3N4G4V4Phksf5Asip87MwP68GbgYFQQLDdz7y7H7j/rLhYkz55EixywZEcPZ8sHG4vT2YsDSXotSuokcfjfmj6ybFQIS1tT2/Ybs3S+KqRMiStl8XDizsU3hF79JBqSpM+oUZnHHnQEfDcvh/uYCxw59zwlh7DrbXMDR1F7pvBTTKNIc4atqb1svkdaLgglFsVEC7N653qyLBd2k0A9FNxWNFvdZUmLOQOHT9+pd8N226rXz5OHqRtAZ9pU+XkXV0rPmwJ4BFYcrqiwgSyeVcbGpJFC50OdNEk5EV6QOzoHaOdExL3UG/KS6Areg8xLm0tX2x8KfMvohzFEfx+jerhdh3K6X4mLiBhZ/UqOD5f1MI9Dz6fSRk0h3JM7H6LPmd6a7tbhbxAS7SOqrsVv9MlxqgkUSGkVxiktwwSZzVE1aK5QAdLXkH6rO98EO5iUHcNxJcokkafmYAnc14GS16qhaCrpSDeXBBvAYS3KtK7mMypvExp8FLA9GLQ9HJQs7lgYGKeKWX/yKGn3TahRTJEcAn2Y+B250jMNEh01VGLioHDsGL0ePzAdvTsJ8RnhwXupkoJvuStootTtgkvpPGDpVOw6pTyPUVcP6Z2N5C/qadFPHrnXbnSmlJWy+8+8Sm9at0v5WDVD5UGC+BNMrGokM0so1e5z5i8dCMieNbzeJ/RiKsFxAq4pKbKRKxv/Xyyc2XoVgGFeI0TODoRzHe6F6/XcDsgiXEzhdqCzcSwTFuaGlordiV33YMhOktUITFRxnZGYcGdI9rp2qm9aDSGnCkE2T88X9UcNUHCPYSVbGH42Gh1FUTR2gq2qY6qGP/hAKl4/XwTmvtK8e7QYh/CbM/eZPfsX8RIWXiJLJScDmh2Q8n+2MKgYk0wGR+w3IoS91u6G2bjLbLRrjojipw/abbo4ELfHiNWg17FydKxtQOWYoKF4S2tSxJXcXSZAcY0k6K5XnyxNcbVFAfUUzkwUL+kZsqbEyoWAYtlLgmjnpRSmAGLqC/Zqw3xViyNtB8lTSqAgrNmhJnlEIkD/d9KUAcGehkYdgZ6betFyUXRKlj7SYNmQazhulFfR+dQREHSdKTedvO/OsZlLLFHODT578oVFcc8lnF8cRssFC1UyR1IMiApb8JvUhiHTJReXin9Bea5J7YCHsBLD8px4NhQtwruUMzmHoyX5oIioPMWzYJUE0ucmUifGkZQ6IgPrH/kW8FaNQyPonF3nWW6/5xbNjPMYxvhoMM4+tCarmtkT/rSHueEviEI7+GaHVgSl8I60uouXO4WqXQuUZFje0AkLVnFrdP3gkCi1Pb1KaNWjh0VunhBF/t57VpkWOZ4zZzvdoGCByik7QjoSqVGs/hyqL/m7/PW+xA9VifLXXqRn+ob8TmTwRKtnGpjV1QCkF8LRaARHFoZiZHNx6CgYfVnZo09nmVqdixmVrA4tDN2ZVKGOHugHmyxQAZVNQ1W/2m0/4v9MKQX3zH36qCZUs6LIGRCpQ0KpqnpvJpZuN4ArV3AbQK9cBQXzh21V3SkZEcR14UlAGlUDXR/X2k6lGRHF9Lxr+7aKaUbOY8gKf8AQaNM7Z2SelvDBLpGp8IhWYUwAsgLFsSUmw2jeKbKcBg+sjFCtL4aNI6qJPGhsjieOvXG6byIpTHPhIMn6DLTKcaALKq1gZxW29UOUbyUoxnLzLEtTyNLa2+JeinI6xm2m98X7CZpWiRrTCirDEh43j1CxW165KK4axbN8zuSrNb3likTznOSs/Awy6E0e0XkJEms/0sntZ3aPqYdeuxCYUYnE0kZ9vW53JYENTLjrO7M8T0jPSAaOLoBiOYJJr+nrWh/NZSiZJQEsIvwfbIsZqV+2eUz0eVniyknpdPisu0Ag8p3qAXEdrO9wOuJR1tbG+4q1qP7E6OcZw0KpB27msYuuiwLj5z9Df7DzG+hR5ZnkVyAzT16nqKDvc4VBydEMrvoiOjLqVYyjVeXV3CGO34Raa0x4QpIo8JgBDueMZFUGVbhLl6fU6AT/DNEWUOC7GZQV+qEUGxxiorppaCq6APWNKaQRD6DltRoSDeUU5aMD25eoIN43bWauFAAyjpoOgiVQDMsWwpFFue72KjTlY1gSgMj9JR1YtzoYp1ikYTJtjMevkblGOEJv+UxpksyJLAFXsGlSf6M2zVR55Skpd8ZIoa08NtZeNhbqTiQ4vQ85X0AgXsGc+Vfs1R4kQEhzZZ/YvL1qRkxY9UIF3z40n79yqudHT+3IrDzcF5QEdlv5ULUI5sQlfqYudZVNszICDdJM0929HhQ+13Tdwucs6ISx/LQr2YJhju62aV3/p/29+Nh9b6/X5Wgdd327+7Q6onhqdmfEbZvsmD3KNTq7ZzYMBJYB26QT+b8Z1ZkNOfsDl56XezIUR8hClQ2t9HTw3ZOW8Vpr0Aux8W7f42O7UTX1AKwsGqN3iFjqGVwtWHCZQOnHLPLNg55UPrtGhhiFA4uDUJATeTGoOoRt5iR1cXgxIL1rOyO/9I36zu1oqa6CJknGbJRdEMrPTjntSMpENgIhuipmz6LDZqBIzCb4psxlRw9JhnxRhegXtXrAVLgmZ4do9ncMkUwH2rER20dBAiBmYdjpIfeDhm0ICNuueAw0CYj92K3DYaS85CR4m9tgi+gO+1n4RjAX9TySMeawD4FIyHI19a/UvPAKNUa0QzA63OG1nIH43r4XZ7eIj7ZGbvCilVau6G7V7rikwouTQQoxp5ZuzHand+qswFcVQzkDb4vm51aIax0CUhyxVLAeM/fxiHL3XLDLUuTscNIfj/ND0+T08JfwA27bftV9dxQpXW5Zr5aGDW7ZbZGhxqRztIzxuzJkYZ1fCK4e5RnMqGELJZj38GIgfFl2mHpxqe9t3eQbh4PMLYIa4EZtU59GFUTYYf3Vt3lItIgo0PoTQ4nTiABXyQTrdd1mhDtoYqHP8UtP2ZOAp05GtFKLMDmjnUqHtuB4BJ2AI5mHMW/XV4cEkEblp+e3rYsstGq7bJ2ETc8+fDF6fMRYwE76/D5iA2DlIQDIGJlX25gQsCJ2hdlbVgRUpZdht7mKmB8r0aS5ppMqiW6K1rc9xv/FQEkWBGMGR8sxy6vwCbS0vfHZAl8VIcwOimlVq8KugmPqAjMOBnt9pv0IRXqjO4Nvn49cFkNAxkkZ+aM4zd3lgVH5YpWdthYaAvOpI6qLQUDp6rPchZcO94N1EIqNsVrIXZG6Thskn4mni5+S3UWZwX8AYqGBGZyCy7N06G8Dt1sc1Awog41/oIU+US+gyDff+Aib8ZQVUV4xmbQuUMxcoBvuYqz6i03z2uVdzk/38tbPjHCDcIngAFMkUDXjUszwZcanSbwm1vEsEVbAelTu/eCHW/e4xrfPbcSQ+UugpE+BtUiw4wKsfCJUk5Um8LgkKyDWJlFMCkThpgmKRE0SEGSYHYZ3rCjKgSf4SKT/2etS/ml/Gc/lGJj731nNz4TuXtRlmT9dX7Or6bjeORur5iiFViw8zCozu+qPwRvZDldfHagYWGonLPNaFZBeQ6NQ2MstaY39f7nJuxL125QNvABmH3ewk6S0pmzq3XhVL45XcHDjRIzyz9v4Z9SW494uNyhGipiQmJZroSU9zgskXbbtZIi5dq6CCeRYC0jBiwR8HVwDLisyoS/4Zw/EvYmwzR16tmkhWesCs+eos6B07fwNznfEt5RQyxxV8076We7DJhxcx5CF9gGVX1eXfUQ28ROWHSzf5JgQRZl6xS/lt77uGoNHNngsx42+g5TelhQgUEoMz2m6jPfqYwVaA/HhPg3vWwU5QcrlApSyFNFQLy8/Chb4k5sIvXmkgnw0AJmJAgb1BDqPIusg2dB355bTiG9k7pbIno4FCxVG25r4WVYKCKR0Rq8wWVkMBiYAM6fjiwtUqQBID2gVlfM6lS9Mdk284Al/zIUBy13zn01eshqAeYC9GqDkEOq2aJS4HiQPn+YQAZzZkzEeofRaKTBVnpMDdLgAoi++Eh9JuMuoDpOCLDXjcIwZCQrd/TdPoGwSAhVXikH0r1kAwIGUrWHMaQDC1hVWrH6aVSiAUnO4IIYIIcu7nCQFMH+0QgzqGfCw6w8MGaQxnojUGDKv8XpkksJHwlPSNJhW31m8KukyKgLL9AYDJG5YQN3CZKohEEHRLljfzaYvZZ6FcU7B4M9VL0+uQMMObvXQHkl6qa+FOhREe8lR60PBquRKUmoYxSCykWG9pMbTyU8XAuJz20YkGHfNQr2CCjPu4P72JW8O/6g6v4JlNMU7qONw42DsgLoh29spy8dzyuK2vxnpKfCUc9GI6eOYrRGDOhiqDY2+u2eWZY5jKRgLDkd9w9Q1jPV4WUoiHMHFK1HNc3pkILzXs3YQBy2YLPuEPUphgiOSVID55PpdgYR9c9GKlFDLn1nn3g18Q8pljRAcrht8KSs34JNq/wyyHX67hSbP+nFrL5TxmQQTOu5yii3rUBPslAsEkOyZh4YC8QWzO5jOjhS6Qu/HA1Il+xxXk1u/oQfXsIWKxIDsxtW701ot7HoomyaC10Sr/i5ua40cY4KePgxlMOz0sVspdWSNRF1eWUWOWzzUlT1y18gCwa1A9rJ+eYlG0uXYtUqNk7wFTQsFO++KEQd2gcXaijDUjMr6+vSG4B9RjxjUDq8yUk9dvt3XKWVzc3F5riDyk2JxR0CdVU2xmqVZI1odlUq9Yazc6VzhMnIjSQhtR62vyDxbW4nNem3OAB3yXmax8QhkOSkXjfA2O7CJ7qwzv8iNFoBeuCNxwMzu4cl4q8eHTNHm10+y8WBJ+pS+qTbGu4hmvFkfD63ycgqvl3vC8vpeHSWStQdhUHDaJHuIQT/SY+O3DqJI/8j9sQbRSG9b724kJb31nUR4hqgmtrKnPzXEov1UI16rxScjKaXlruMrhfWFmcXWGcHbkTkWHuIkmaJIyOuZj4GCN/ypgdpRkuYubPyx+qo4UYVU6fnvQ4ZCfXSVL4Z5SPJ7HQuZrwebpISfZyQqYYZoTQWvTmtneTU9tkPCjy8GAm1svCGMU0bYhAlOU5rZly2qe+hDKYPQxY/l1mi+YY7bQkAACz/0wmeD/CP0UzQxq7CRZLirSb0akFYZN5CwNahoL3FaK8tCykYY65wJkoohs2fwzdjYk9+e6tF3Gh0LhZcrAgzAYXiGQVZtdplL3kQcf2V1gIm2OecZnYl3CH4mQ5zyfRx/zLBA1J6voshfxiDUWsXJFrAdp/poIR+AIrRf5WHAXwcirCKqLlNOD1mgLUNtiN1HMhYnOVA67DbimNaZsz1GXKXax+o4gqFckBF8t6XSkkTxWTF30aVccrhdF3RWZJWo8kTiZVKlUDBKRFKHuZSBaqa5ZRINTZh04I22TWDhPZnnjgJOkKhKGd6Wg1sf0+sn1lLRFEsMc5VVePlSJV6OEsi1Ja6OLjsvUGVcI8LDd22AWKQ80LV2aB4pBeoGLHAe7P2EJz1hmysJ0Y950HTYhLbqkKPklSgpjEwA4OXMcy7VE/NBDlP1YwKxFQorP9SoFjhPl71tQ2/
*/