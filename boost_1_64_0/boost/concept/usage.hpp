// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_USAGE_DWA2006919_HPP
# define BOOST_CONCEPT_USAGE_DWA2006919_HPP

# include <boost/concept/assert.hpp>
# include <boost/config/workaround.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>

namespace boost { namespace concepts { 

template <class Model>
struct usage_requirements
{
    ~usage_requirements() { ((Model*)0)->~Model(); }
};

#  if BOOST_WORKAROUND(__GNUC__, <= 3)

#   define BOOST_CONCEPT_USAGE(model)                                    \
      model(); /* at least 2.96 and 3.4.3 both need this :( */           \
      BOOST_CONCEPT_ASSERT((boost::concepts::usage_requirements<model>)); \
      ~model()

#  else

#   define BOOST_CONCEPT_USAGE(model)                                    \
      BOOST_CONCEPT_ASSERT((boost::concepts::usage_requirements<model>)); \
      ~model()

#  endif

}} // namespace boost::concepts

#endif // BOOST_CONCEPT_USAGE_DWA2006919_HPP

/* usage.hpp
p3HmO8LFXRaAl33vFrdW2PKOU7W2e5jazNQwq+/dwLgLV24k6h1B025lY4Cr23Acttuzl6MY22/Wzs2UrpOpRh3EyS31OPsu7G+vBjiIxCGKsHNvJ7tX+bYM8/z0cZuO7y1QxsGrA6b5zce/KN206Ti2zF+DYMBOo/xN16Q0bZfR3nxd0xf66mXOaoucQV+fvFUAv2VqCm/UoVvtV/6J7rUKKSPB04AJ1WfLIAIH2lNTO5SDXmyMVbvCd7cH/wgyuocuKZHG40/wEVW9xZu8grI7A1ng5aV6ByyN79UZCkyfq/MYWHYXVV838+pxlnhpHkbJxt+tHFI/Rqyo83+yzkiimHuuH5WxbtQPX4GIQUmhaj/x1TuCvcm9nf1qTl7ea/BFFe8G13Hjf6bnTKEbOoUfFUN5lS6l3rvbzdWyebIShGeIM6ZN83wRFdLxhlJANcilpgVVeSZI+ikrXIjcFGZN5bmXmyXeaHGwPJLIixkP4tJzeU15yoqzi1OV529meabdPOFBweVQiqp25FLwQ9dpbb76J24FnLpdDHLaur7+ju1F1wggK57LVDRVqigoynfTL73mum209P/111uoN5IecA3WAgH8DY6UO/uSSL+tPDHASJEU+1v624/Lbxgysfz2x8G3aK+4l9TyYW0CM5nJdme1XAusYnrIC/0aYwBdb0zlVc34Vw1/ev6Y/g7vKTvogJj4L7zyZRBD4kn5m/R3baWuX+EvV32HA8FeX9smvFuJtEH8peFbhStoWtlR1exMxXYxbeMlVyL07pJFZ1ch9FK4mfbJqyL9+Kz9fvRqJg2TRnrr6iYdk0bZ8TVMOi3XzmtVtBU1iVxWm1FlJaAezyC9DJGOMg9eG76Xp6qofHyDcx1Cm+uqEpu6eMRWpGtlq8Akxpxt/J3lnO1QJwrVVeRy+61zRMWY6OO7fj23a8IZa7M7auy5Jqz2Ras5MA/b3tWI76lb4Z0qD5c24mCNVobNwfy23tuEPVJhMb8H37cOVqn0iB57d2n8ySa8XvPPLcBy4ph6QVO2uzEs5wdG+fo91UJKXRvlbMShrg9VeT/fhKW6XqjywD7YgNe6bmvcmUZc+Ti7DNoKuT4B96eqtvShUR5Ap/3lHgSlUi1TpdJbnlOaUa99ANaqeM9/uEanG+Q9ubZeXmcOq4wSZsWCvOyjTbxHmnjxrdG5T4zwwlQV6ec/P0qfm13EtwfsK6N0dV4CV2u72BbqMCudmdVhBXSruj1Tj+0tDdo75kt+YxQHVhB9fJ4dpR9TJ8taHdhvtn2nQXcrBN6r5J774ShebT8qr7fHjqvhpIP95FwTbuXBy61hPznnahx0PkSqquou69GttYAyb6CxYAk1EkaHdq98jr+CuOuP4hSkDVjAVWmf2jqKG4R8wmfAC2gPr9eMNZ8E41u3a4/gtWUpBc+i34iHDnBz84hSJx3HqwzMot+IP9C5bZq4AXfkxmPV6rkt3lmGvaCxwCPtozyeMWPNAmakbyB9fDPSzTaI9EuvhHTSd25ZyR9Hel1bQtza1SmOtiWwAzo/1wTcxdmfXRXvdYB3w+MBvs0+sxX4NjJOar9Y10N83TiJa7SXXL8BhxKH2PvfALHN46TGfuJGgL3wOIm++W6M+Pq5hcbd7SaIaxzX0TfWTRFr20yUN3FzxDTYTMOH+nbE1tlMxL3gVoirt4nVXuBtAHfB8Xgo97ZNeFqnp2/XhMM6xbZ88PaAvbgxDe96TyBv3RwF0/B3AO7ixtx21V8mgXdDcwvU679KnguONZi/S6cBf3FzkWp+N/HW+nkMWNflLsRqISW7LNrtNzaMhzDIGGPMxOsIDscYwAKustvx7027nbLIyQI=
*/