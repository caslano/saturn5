// (C) Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef ITERATOR_DWA122600_HPP_
#define ITERATOR_DWA122600_HPP_

// This header is obsolete and will be deprecated.

#include <iterator>
#if defined(__SUNPRO_CC) && (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))
#include <cstddef>
#endif

namespace boost
{

namespace detail
{

using std::iterator_traits;
using std::distance;

#if defined(__SUNPRO_CC) && (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))
// std::distance from stlport with Oracle compiler 12.4 and 12.5 fails to deduce template parameters
// when one of the arguments is an array and the other one is a pointer.
template< typename T, std::size_t N >
inline typename std::iterator_traits< T* >::difference_type distance(T (&left)[N], T* right)
{
    return std::distance(static_cast< T* >(left), right);
}
#endif

} // namespace detail

} // namespace boost

#endif // ITERATOR_DWA122600_HPP_

/* iterator.hpp
CFWFJ2aBRZ0hVGeQaW0FEvESV/fEEm7AR0DKtIDk6MPX4E/kk6GTKu3Yg4RtDvt2SnnFwWpBSmxMt10iLUKmVVDKm1FItayEbUmJ3V5tIwtGBhWsZyzYt8aG1kd5AgGbRKBYczDuQEaICHiC87lBnp1L8pUOTMgpZQkHaQld/lCKfBMpa/sn5Kj68BPAKPKl/CfzcbpnnKHbnT//E3q+DS0wzrf6N8n5JpnVww6PzkjGPTC3FH+thE3Z/Lc6JTNxSk5k9IRLjyIYO3Q+GGEX/pkJJRDByDBYeQnbGLUXJtkNqQUwhN0BguAVO4xK3kJHjORF63IR5nIR1uUiRTk00gIGAdajmQ972owHU2jSQhb2blon6jxwXkdOoDzilbKchg6mNn8rV/p0TYCiYn7lyfmVJ8k9YiDNw9rKnYfl8JqkEYo//Ix6pg1NT/Fj1pf9dr1ZX/brxSfXt8mqlbwq1vJ3tNlgJa9PtwcOMCsKR196i9q+vK4YPoPjENb84PFGG6rxRgcydseMVJ6RKjIyeYaLZ7jU0KCWMUNddYgZqtpLeby7T57vqyU/zP4TJbtMRkoqsWWMNHUPPlpTe8heM9QPJiFUfoDvSKtsJ78eM9ejPTZIWDOUTNGVDh5RIFM7NFMWx6ngzawdD4v3/nyEioha4MWlz0KBCfkialjGWDxGvTSdjlFFg40vWcJqdwHKHTXsU5EhA+tdOQpPDMlsKcXfyS4ugf9gFy0UF7HTY6JozYcnlAD3ZuncFXuMOR6hy5OBGHxUaF0B1/qtFjBNz6A0sAFmTpvyDIpPe3qeroNbHkH3rQ/JZ1CWS4G6y+VMZB8ACrNPzqWrnjLODgX4ukjmzXT7K5VrKXbu4iWvhRDL9CyOJYR+FG+nYE7DWTznI8TzIXreajBDhrhhzRyIL/swJWfw5Fztjc5mtd5qAVlpdutMDnyuzUwce2jiLJmrx2LcSMTZsc6COEmXsdMG94Canw5W2ti6QiC3dg3ToNFi1iar/DnqxQ3rROd2zRa6qwvS/8z3E8/0RxEwjlwb4hVYuHtFGqtTLI9NAHZ07Aykfpm/a/ggkPpWIPUK3f+fHcBwdlXNtvOaYnIuvxInZzs/Tc4PLjJOzhiqdpFdb5Clxmu9r5BB/rK8AqAXWUrIBj7Mp10gR5l8QvPYRXDXh4CsXZpu9xPTfA+gvm2gnDgehIwTp2YaWf/Lgzz0FSZOBiurWGP/0pcmWFb5+8Q8XdaK42kJa57eEIkRtA1cJnrihqM1R9+NIIdy9Yn/XIJIVTG+86dE+XcfAMqvMVL+vGFiXX6AVYT1998ufRj2l3Lc/6+R739OlF6za1Xu0waPVO5lMlWGVJ/sToxESry2RqovVurxD4eytfA2GAXujsqsqYABZo7e3g1+fTrKMgAvloyfbqEraUqNXYWNTTE2Vu6D4LXYGN1u5SC7L227X94h/XYTP6sd5W6+Gagxoczj3fUFvi2188tqaGeJsR0ftLOFi+oeJqoLS3cPBuzN8COEcwnCswihyAghHiAU2MnrFQL2ytsefDOz5zKM1oszvBuBuQHBrDGC2XfJ0RrpASaDkMN+wrv7K9rC4bt2giYoOCwZad4JPpP6nWfEldhBYb9v2hwputAxuf5jrSU381qAnWhLSB0+nOhyYIc151caN0H3RTJMOu+4+vqd3zC3l2JwivuaYXw2/niOOhs74dtBRCXvKgsqPTiEU0l2cesMcUVS2ZvPT37fBHcgnQrwDqT8f1xpZSnPFqHi42qz5Q+FspbhPlacjbMItdlf0lXUGyuB8pBbMUFS/uyLUZt9G1OiylPayy3YD4M6dngUREsZSlvRumnmtygaRkkpEf4=
*/