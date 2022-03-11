// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP

#include <cstddef>
#include <functional>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/geometry/algorithms/dispatch/expand.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace expand
{


template
<
    std::size_t Index,
    std::size_t Dimension, std::size_t DimensionCount
>
struct indexed_loop
{
    template <typename Box, typename Geometry>
    static inline void apply(Box& box, Geometry const& source)
    {
        typedef typename select_coordinate_type
                <
                    Box,
                    Geometry
                >::type coordinate_type;

        coordinate_type const coord = get<Index, Dimension>(source);

        std::less<coordinate_type> less;
        std::greater<coordinate_type> greater;
        
        if (less(coord, get<min_corner, Dimension>(box)))
        {
            set<min_corner, Dimension>(box, coord);
        }

        if (greater(coord, get<max_corner, Dimension>(box)))
        {
            set<max_corner, Dimension>(box, coord);
        }

        indexed_loop
            <
                Index, Dimension + 1, DimensionCount
            >::apply(box, source);
    }
};


template <std::size_t Index, std::size_t DimensionCount>
struct indexed_loop
    <
        Index, DimensionCount, DimensionCount
    >
{
    template <typename Box, typename Geometry>
    static inline void apply(Box&, Geometry const&) {}
};



// Changes a box such that the other box is also contained by the box
template <std::size_t Dimension, std::size_t DimensionCount>
struct expand_indexed
{
    template <typename Box, typename Geometry>
    static inline void apply(Box& box, Geometry const& geometry)
    {
        indexed_loop
            <
                0, Dimension, DimensionCount
            >::apply(box, geometry);

        indexed_loop
            <
                1, Dimension, DimensionCount
            >::apply(box, geometry);
    }
};


}} // namespace detail::expand
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP

/* indexed.hpp
30ImbirSszrCVAQaWuc1JnA/QhwBVE68gQP2zFNKJb45oKs5OIlOTVgkXQHF1EYznGwMUaRno6+Ivdo5ZwYqRgU+sT0L3t1T1dRN05djCAZxA/Kb3VPCEj4g11nB5sS2vTzen7LQ5DudJM32nc4Q1yOj13fa2pTsO/0NKd53OlNsf0qT8ug9E9v8pO3DLntRDFUY0ffkYN+H5iMM0DOx/aYRcgP+LZ4aQ4wZqGpXSXJ43zxoDW3A+OpNEt8H4utNGWwzlHbVcJ1k3CqHYC8MDSPMsHN5UbzY9i9SypnKw3/6WKJkKisT25Oixs3OufGzExg/Ox+OH3Y7Rj53hAYcIls+CF8ezvdEtuVTeclUUwX2sEny/5I4uuGMzZY8ZHI5gxTO0BXnw2YLJ5LYS6F29rOKZcQsmw+PN8NjYBa6Ogs2mU1NSpdr9c/E+smO9NzRk2hifNdvRGHoTwBcCG1i9puThQnYcw1+O8Eea4AlqZTcUSztM+hUpaREuQ1wPS4bp0IcfyPlwzsd7YdW0PGVUrCowAaH9KJGLBosuRCTYiApwqLKgvX98Qa93aehsK8VLvRrlNIMvJXJrGrE0V2KPFWh2z5ioZ9RZNWxkTVRwtJlvRHB1PB86/BmCvQzf6+UwDtWMkRxuSJAL0mMSiW0Id2JglYpm7ZxUIL8DvasD3KIr5MzBrfRwc4yEdkCyUiR3KBNphn7L74uYx7U/2Swx4DAGXDB81H+fEBJenmW4gV8bpoyBb3QA9mHzgiBzE8J/G/+x0H9UVeVi3+BxtTUAhhJ4GeRcbBQwHXCVm8CZKnvNV12iHb8V1LkOuLhiYouPAQKWOcfn/gVWv3ANgCSVq4fY1efxDvn3lvh1UYEXWuuLk/81zUJ5NpE+rmywIQhdgjpfuQYbVKvVAxFOA3Y/FdqlAq9lxUuhNw/LSSEFNu6iO2TIYhtqAKA1RFYnCiOXI5ByDTGu8fkKdKEkoHCYDsuZrtW11BU9rFnjp9RgXRSxrR23zXgFhkjxwzNKm78cw3f/v9LrImdw5BV5wJxnEIto0hc4ZuKCAaTmirgrbE0Qt+UGE8YVOjBl/lpv4gYJ5ZxqgzvB9nmF/i+fKICfuUjIccvVZEaLmm6HSx6VGwmKQkqgNpmHkL5yImQ07dXVSM5fZPrgBrkAUUpJGlLCmI/JMlS3mEvbhpWbTNJtvItTXNon5TBjj/DdTw8qVy4d4RLU2c7neqNjsBlit1c6KAwdDfC7AREDhXzT0pJmKFGqbCwomuSgq7XrtlERAWqWEUarUdEG0e3ki6CXqdZxsuEQNVzZTpAXlLZbdAl3xFDgQE9HKddh3hVHDzMDnmM44LabZqjWnQN17D2Dyu8/soU9tcHgcwlqau/0sjefJD6Ex5h2LtzGdqa3lHFnVVqNFeb/AvcdKzhPMylvc1Bh43tn4fYR5tSOJrf5bmR4KN/ydrF6uYRTc1UEbrbsZzmmFKapgOx8m8mCxvqlfy9HuNeuxIFlZ3iGdFp9FqcqvMbh9W8ekVC9PmH1ycLQ/9LxAOP31h/hMc9lOuPcXuDGn/FJvaPW8lJSzTnElBez2bOIHBHYYYT30bPTcgOx7c3F4lCw64S/nJooSi4VWUMjVSO6BzjCQMyKIJSNuq2+pccQQ++9k1QVHU0kltu3u0FG9E1GlTogwrhFx1p//VWJJ7ayP8pfGZPOEK6tTVAJiCrssnoYs+LJ1Q0qq40wjrHyEXGgEEuNcmlxmVdLnWNka3Xvt+C341yFH42yguM4/Wt3/30q7A8pagREJOoLqUwQyu3sBH3FSHFIvvyl7r6myG3oytXDy/cwH0//yGkmD4YHsBuTteEAHaYxA5fO4mO+s6XmyLxyiUmpbP9IAD+j1+KF9Z6JcFzSY1yj5E1qChzGIcoLYMz58sQxutfmPcWSVET0zuhK+T+qQ2qrtlbKAnK3UYmTlYxr3fZOFX6hzajJnq293av73lkHQu+57lpzf7uUgnhUndp80qcmwcn1X1/Rvivdd9XblY17XSonFqWd5Ne827SdAasipTVDe6Vtaiq3jxRVT23A5p2yKWN3etRQkAG06VeNXUXti+vp8oex8pCkQCvvRUO/ZnyoAI6DRi5DpW4OaZxBT56Dur47WfnoafslYpIc3Y0IEdbU9OPkdGLMBMjNCgLJOz5gubl0OOJLtarSATmqgGI54Byp0rToqRb/cubnSzp3DDpZBtQJRvVsM+dHVb9y71OdhIfSNfbUcM2ZQCUvQX7dzFt5Cm+fAHubP6Zbfx7sgYUsS+BUp5T2/J6JtvRZEFe4FXXNDMXVI1q1LfQr5ctwF9SnFZfbyO9ieOXJQka6J4g3UsPcUDTuCaxpQYNWwGeduDs2EodHnNuryzC2R3aQ8RLSu5BrmGQ3wOzLNeslGsapPvze6RptqIMKdlWWuiJdxvZl79AZ2S20jSpSqnMthWNSgtRD40aKm2miDnFRtJj7iTL8imku4s6duQkuxwZqaSwm57Fo4ZkZME3TWG32KhUNhtKG4YwUio0PRObTmPHfqoDBEA5GwHl9FInHE6uEOtiz/1cVcm/eTfniibmROrBTmr4WNnImYiNyAb8Pnsw2Mhy8iVQ2hhhUahrrTwj2RUAy9W+jlh3CuSqy+r0sVh4WJFVWuvrNGSVNmTZxwz2EW4MWVrrqMKW2I9+LiKht5ZHTiVTwzuvG2eSQxpcULehR66sw0UobYY9cjPtkQL2zyf1DuZonWgMdaK0GnuhNtUq8NRhcMAkWXiL6Dxw/G4/lhYe/pdv+37Zw1jf8zCRxY0kRShFKUJRGNI+IysZEfQY9sZvSSfXrOviPoYbaFEjP6GLGsO0cOX7GyGj19aaIa1GvVm0ZHILW93nNUMmuuOSaDT2EX9JVKy/4liV6mFAnnBe2yEEFMVwXUi5gJHeLASVRIsbg1gb8Tl89wN1I0Lrfh8/S9OPJAtB66cz10b4geDLD3O7jOa2lm18Qp/bcpe/tdqla3J5CmAfuEIqS7iS576NtHpj2MREzUoWXGpTI4tqHlHdBrfBxUc2CTb557Ywc85xCtM5OjoJzeQe1gVsiFWiFui6FlM8UJtSEj0gn+JxUsjgo1U/TkYA2w1YHjE+66zpiGzCXxr8pcCfFb5lJnDdVgt6eCpAXYcFM4gBOg8t/QK5FEz9VuSAzueX5yeZqOiAgS+A3kuxLfN6RP9DbaRPU9bIdnwEG+KspxdRW71lZklP0Lwi5YxDMI0CW/eCbjjoTt/5uIz+Txag4CC3Yzd129Mn24/Kdlj/I7J9QLYfA8oU+wz71G/vI6fFj00ndDRJqRhAbVXytZ+Oga89fWzLJQkCe26BZYLyXiQ8tJDEjYMApcVM+nO9YhvCQdwP3ByHNT2u7Qmx7QVCNADocSLLZk8R2wiBJwgothHWb0+TpnMBBLIOL0beXrp0MVteoaqBVI2RKAVIFUJXgdDjjlWuVOKyOg0LTO4pegCsNCXOgCkKgMWmbD01Q1lgNiwwUrRDKwFVTFSbRhVDDaphNAbSVY8VxSsh0TMqerucbKafw0gOIYdmRQqeF4bdW6z5Mf006I6RIjAamtE5oRnNiZCxlaCMjRX/LFy+lj6ZfM2qzMVDktXp/hIHQVoJVlQ8nIuaF6iNzD2E3PNdRJlR6YI0lOcKiC9TTBJDA2LMJETjBY0leiaUxvFMH32XJHEZGA7IL1nTDTyISTaqRJAULocqmBOU740WB1vPcbDRVdi6EKz4HK94joO1fxcvIaTvqhwUddOhqfxnopoDY59+rurCugI+6dI1kwrrYktIduZlj/x6nLBuGsBvJQOFdbsAX90L2N7kArs10oWldVtKxgshOIDpgPs1E+/XK212k5RmIzxNssAVP+NxUXPokReIdbBEeJ2ALxJjC6ph13+I4SWU2AYETiT0wUv4gtln/XfZq786uw5E3rrZIuSeepOLfAASHMXgtp4j5HpUByEEPzwm2XOOLU4loJeu2AcArKUCvOPQbvRKgnZ7pYuVEYQoLX3s5osT0GHSLcUkbGKdz0U4hkEKma0ZJ5r58PwFRTOYvey/yz79P86OuQNcSoJRsJVCwJQaoizhIhL01z2x0A5eKAkLAVS39ScLE4UpmNEfmVHBjBOr5GiMXGqFSxJyFxGnJV8TrkhTddnKVC3Fk6zDRh3Y4O482N4hbtmzmH34aPjm07VUDhUSa0DV3MbgVq8OimYXHDcC2Qt427lwVks9sloSydpxHyu6HzD6JkRNLKjr5lJza1h6WpKQqy7QRIzRmKObuYpg3S1hVKs0g4aTMo5xRNMb5peNJQ0mUgj0Erm0TC4tl0uBFqrujm2+73Zvd2lh1KSEmvUrCbWhwLaYcPyltNylzCuZutzLa0Vvtw5knzuCT9Xa03L0+Pa7UGm+RmVSUpkUoxSVB0xKkSNgUIogvydZKZqDMvOroqOMQiAeFZhnoLrQBHGOr7VQkJKhF0iLa9mQx4ubFMZawrYOJArjdih6FHqgXPA4a9jWh79Ud8bMB9TFbXYw4T2AOHNzkC+jvi8vKGfr8fNU/fPfDooCfXCwH+CHtpu0Dz36h+plpPfZvYCidbB7oe3l45jrj3+cKPhW5QEsPXofSai6xomnMJklH0n8SvEUZhoagqoiCiNukAeI8bNPxQtaqJfZSoXZoYXfdrCGDYnkXwBuZKUyDy5lwJWJFw0YrkGLllOvO6/33ZuH2jBLoDJlYR7k3NwHecYvgN7m7Au1OfrgBdscmNDm+Fr7fhmsdW5Erb/ktSJ6QbWmhWo9YOD6FlfaLVrlafrJ8Y7n93jD+D1J/sn5PRTIq/XpEL/nhnB+j/GtCfweTGKBSy7ok8D+gKpyMFHZ3B2b0gzrPeMzI+ejrCU+CvchIE96PH/6H/BR3Nydi85HSZ/Y4G+GjILOWuGMFFTOCLP6N/PGwzgpcpG3e12bzkVZR6b864gRs25T0FAFQGMMMlD+mB9koGB7unZFpTeMh+IN56GUNqPh/dQmMrx/CTrM7iiYnJ3yR/ioM1GANm30L2h2wMDYSQ8aRlPQIe7KYFL9NrTc/+IB3eRd+iaZu//hs+Ewc3fkrTwNKVgxczWMqOu6N5FYQoHEQAEamhd+xtkieVjwFq9/DVLIphq292pSONzP5t8zrDpZ5fd0e3TlJDND3gmiuUnZJIQaeYlRYregNKgFbbHNGGzzGyjuAXpMinWy05sQQXLi3TJAW1KOk5cbhz4Q9DgdxKEX2x7lLPyZWCzNtqzQMw2wq11UmHA0Km1bhqyU0mxkTi/kxs8WMn7GcI9m1LXl9FuabgRt5UbQac6Q8TOpPFOUcuSlVDYE4CqVl6HSqpkCbqJhsuFuI3RzjTGQC126CLs0xcmuixwJMlQsuR0aWwWZMssaWKkSyVz5/aXjmCvatBHJ6sGKG9m3ZP1Ir+ScEU7kI3OkUw/9dhDQ0wNwS7ncKVVKZV1Wj28I7uvKWsPb8K8XmRhOVq6I6C8mZGL3ii7xdTobXtefI5USwq2ao+SquggFqfSdc9DMJdZm0Q2TgWz85DHkeniJ63E7cj3qwoh764xIg+TdT05ukDxETBCvvxj2bt5VyfisMUS8EQwRLxqGoLSNrI23awbFLUeIHHF/ibz/CMaIoeKoYpArjvkrjlSpnj5kihwgpghe+Wu49n2ezhRBN9KucJxEw4oG2PX/MHIdLuiifcDBHrOi4GSALCNnqKubIV0m7XtmRVX358h3TcCMef2Lmpl4D6qlDSBq9Ondwypz5YVpX2lY+E03ktaZthOCzItHOPMC/e96RvylMD3Toe1uex+h65oQ5YhcPyDXh+Pqcj2Z2zwfT7j6DUrLQOBa4k9UcP4EAfub0zT+xFTA2pMVC4AjCkh7iCKTed4BLF5riHkTkS9hI08o4pYO1nwjR+mP/yQSpYdtEaFErpGj9DLnGRTrjMNqJiGHLbo5xSIvMRjQkqLZSg4skdFwfZTOaLgafUklrQ8yGtBJaO4pmydNbEP1/aBthdj2S1LuJdvt9CplHwWyR++b6MVJsmZzC3Pb3GyUHpps20nojuHkWNEOWDnokEuPlpmnWUNkY/zzxc2k9a7xNVp0vgapwGt8jZY0KTtk5DELDTyymVygqoFZmoGH2HYHKlGrC4bq4Fe3+nhfZ3X0FIesPSggNkK4EaXQjHr1t2UbkDAngjxMoT6HFOrzQgr1xNfYN46vkemqYfZmAk8aiT1lxuQK9aXeoDlsDDv7GGkmB9l6iDuWesPOfM5FcDh62NQbRXJFSlJnPJFhFxthMDrDZFHb1zNMIu+aCQyTqRsvpJBsajG4TbpC8nlSSD4/mUJyylcqJH9QgxErOTtC4wH9I21SdsSaXNJ0RS1sJvxkvDZvDatBS31yPE6MCIx/q2nzNkmsZ62mzatK8UocxsvUORHdLGHOZJwInMccmsdZ3NMe3JFPtIc4EHFugW1o5/oVsfpFNQmGoRhQh54Qkgf/Thq41zjxZckPYP9TK9PVpuaQOIoV+ADOPU9wbiJ2cMxC0RuL0qRyG+FeUolSlW27eVQqUO6tVu5e6VSW1indWXsNXZw3Zx/xG2+kF6WqwVC1ApPGlKJauIfso/KSc37PyG0Bg//uaryeMCTa1uUhh6s6BD13/X/Fx9honMDHIKiYPW0CH+O+WOJjPPhNDvROP/IVfAyi72mqDxF2M47ZAPsk6kfQ2Vugs7grILfvzhGB3UhxmrlXMWWEdXzELxzoNsWrPSUl4hJWAs59KWkMsjPXjze5CHEOvP8fOQfeIOfgad9EtpVmXEvAsRoaCVrWbggZ0c6ZSnpfczSIAClXTCX7ycrqMOPJJq+mFxYzdXKD2v9Og+S0sgZvzZPSUnIFqWl+lYc0SO4ZDNMgicPg2pytUWFxOhGyIcoWiAHsU82pYVVxIX0Pm3tYN+74Cp0PJND+E9bGONWQmIeIIVTQXZo26yt1Pxw/W066H+/eOaz6urNdqPmx63vjNT+CpFbfz0+S3vjzuyiaEulhdceea76QZil+Yff+4qT6VaQ7ZhqqhkycfjQ1R2gAIAhZdz9pgCIcEdsP0j1o8o3FA5gfu8SziM28gXbGzQBNp94wQV/wnEhfrdq++Jeo6wv+ZRfpCxasQ3Zx4dCPyL8/10HpEVGRzuPW1Sf/KAA4WtXeKdViy2y2ZPexVGmuj02T0suQYVPmucnhaOhG1IxcRDcISMnH02O0Icy/bGALpUXh58/o0YCPH6OLi65tJ9ULqSp+Nh/No3eSUibrPhdpqYNLc2dyMIPAnscME8mqlBry+Mj1tdibuJh6lRKU8O2mZfVcj7qIyFRHAQwcBpOje/0uDTpjNGwL/7WQTmLdLaiTGOE/EblQfIfo8+lNJsXEpGAHY85dQDeRthSpJyKRKF0XqZ6Yk0zqiZRJfH3tJk1DcWlHUENxWVJIQ/Ehnk3eFKmk2B+mpPjXr1JSfP2rlRSf4NwQnBbW+PAFuCHSRG4IJrHBhAtyQ6p/D0vxPGrvonyh9XZv93p0/RgHf6u614/RQqgx3nnKRGYZO/510QJGZ6/3smuzghE6Oc5G++EhbBcpEbtFa16mhjfaUzZQsxvtGbxDG9afhtdnsAu8I4BZII3/Olea/hMPZrAdWtmTHtny9ll6VIUf/k5vzaw3Y9GbSeEN4I28n7cor8cOsRriwbClWSHur17z0llB/goWwKp9u2kUniQ1CTuJCCZKEnnsg2d/jxHcsnSOSkM1dHrnm1jTj2aR5POw0+8nxbahXMA26/z2LU6ifcjcduODY+Ty7oCF7Gqdrg32FxtmX+0BGm4LYAFr1fedDWYhRYA6nkbHrFuZiceBtN/3paq+Rg73y4xs9Skjwqa5Wq7Kz0xI0lJ8JftmCq/ENsYLTldDM1ZdsaUKpWmouIb85Q3153i57nb8d1vzci/74loTDVDr+u+h66xklj7IwMV/3IChtL97Ln5ciJt5W1rRrOiIxrOy7HyzFzCJmGssAlC4iEUo8zZBjnZVbPs9WZoWK934gp4/FCD77MeUtbiIyvz2UiCXCJY2GdmfDQIf0C87lU6MA6WUGil08ME7tNDBdoYrFV8/4rezwFS//SjixDt+d0aFqfZVjEQrcEqOKVNqHOojB2hvj0RLomI/Cn36Eq/Rf2NFMOC2+hFMh9pGzmP6h5AOHWxfgtNwDYyji/1CDsq4hZ3fOwvjuyqTuA3+9ekUfrfCxL73/DDtSjVHqUhBYDmlRn1klO9FrNZ3Bzf9+iAzYge+o0JtH1zNaytNJ1uyS7WqwmpPRD83FSm4EaCBKVB/ZO1X3RG0MZuhNfTD8IbMO186Ag39EBtad47E7yN49ACVw3VVWkxrH7i4goj7JdDmxgWXbJTxIG3s2/ju2r+L1pG1fxtZ+4koGb/1nudwWy/89njegwaVRmPgEjLqfABd7d/gvyW9yg/b84MPCF9/uf2U52/uWdxPMwK5Vb4H0gulJ90pzLtRk4wyTTJavHHBxRuXX+LrTkdcYoPd1B1rPggb07J1WIXx+itNdAyi4HWj3bSh1Aznf8OyJLnUIntMgXg29mA894OpWRajW+ZGI1S8Wmk1AfT0249BY8oNDvbjF8+oSp/fbnYo72i+LFgLpFGMxVy42KdT76F+8ckunNLuFcOa20gy6NsJr22HJXRdoVQAJGRs69l4wIrR0a/ga7EIkoz/ehJ5BtY1Fo94Ahv4xjjbxxAb9WV3kI16L7FRv/9/wxO9htb83zD3GlqBD5rX0Cin5jU0jxJHKTGbnsfo+QsT9Eo7pmjAvegsgJB3WBVcpLrnzwOdQPsvRG7sHw4N624/f32IM2afgl/d7WePU3f7KVNG8izcCo/iDq21RaZJiK8aZS4CATQB5rvlcqXMxK2AFxrZb/8Pp9sThVbAf9OlwSxzffDQaWTsy1YErw3E0rJt0MnY3FNAOOXvl+KY69eAlozosvSHN2nK87FwS63rRZyjSncIPplU/aarwmxgTTt/gGDsJiu/Go5xsy7N7PKhdmI24FFd/ax2VOG5+VZYsh0DnDLybqw34767gW8zNvM3Z1R/hZm2sBMy4gaBd+kqdCH6m0N0WpZipbcY2aanaD6u+NZys2RfezYqcBEKIEZY0/BJTE+AJOnaPPiYieEhUcMUNuWVy4bRxa2iQYGUZQgF2PestOUAEro=
*/