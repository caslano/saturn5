/* boost random/variate_generator.hpp header file
 *
 * Copyright Jens Maurer 2002
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 */

#ifndef BOOST_RANDOM_RANDOM_GENERATOR_HPP
#define BOOST_RANDOM_RANDOM_GENERATOR_HPP

#include <boost/random/detail/ptr_helper.hpp>

#include <boost/random/detail/disable_warnings.hpp>

namespace boost {

/// \cond hide_private_members

namespace random {

///\endcond

/**
 * A random variate generator is used to join a random number
 * generator together with a random number distribution.
 * Boost.Random provides a vast choice of \generators as well
 * as \distributions.
 *
 * The argument for the template parameter Engine shall be of
 * the form U, U&, or U*, where U models a
 * \uniform_random_number_generator.  Then, the member
 * engine_value_type names U (not the pointer or reference to U).
 *
 * Specializations of @c variate_generator satisfy the
 * requirements of CopyConstructible. They also satisfy the
 * requirements of Assignable unless the template parameter
 * Engine is of the form U&.
 *
 * The complexity of all functions specified in this section
 * is constant. No function described in this section except
 * the constructor throws an exception.
 */
template<class Engine, class Distribution>
class variate_generator
{
private:
    typedef boost::random::detail::ptr_helper<Engine> helper_type;
public:
    typedef typename helper_type::value_type engine_value_type;
    typedef Engine engine_type;
    typedef Distribution distribution_type;
    typedef typename Distribution::result_type result_type;

    /**
     * Constructs a @c variate_generator object with the associated
     * \uniform_random_number_generator eng and the associated
     * \random_distribution d.
     *
     * Throws: If and what the copy constructor of Engine or
     * Distribution throws.
     */
    variate_generator(Engine e, Distribution d)
      : _eng(e), _dist(d) { }

    /** Returns: distribution()(engine()) */
    result_type operator()() { return _dist(engine()); }
    /**
     * Returns: distribution()(engine(), value).
     */
    template<class T>
    result_type operator()(const T& value) { return _dist(engine(), value); }

    /**
     * Returns: A reference to the associated uniform random number generator.
     */
    engine_value_type& engine() { return helper_type::ref(_eng); }
    /**
     * Returns: A reference to the associated uniform random number generator.
     */
    const engine_value_type& engine() const { return helper_type::ref(_eng); }

    /** Returns: A reference to the associated \random_distribution. */
    distribution_type& distribution() { return _dist; }
    /**
     * Returns: A reference to the associated random distribution.
     */
    const distribution_type& distribution() const { return _dist; }

    /**
     * Precondition: distribution().min() is well-formed
     *
     * Returns: distribution().min()
     */
    result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return (distribution().min)(); }
    /**
     * Precondition: distribution().max() is well-formed
     *
     * Returns: distribution().max()
     */
    result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return (distribution().max)(); }

private:
    Engine _eng;
    distribution_type _dist;
};

} // namespace random

using random::variate_generator;

} // namespace boost

#include <boost/random/detail/enable_warnings.hpp>

#endif // BOOST_RANDOM_RANDOM_GENERATOR_HPP

/* variate_generator.hpp
zKmO860zudjJ00FUykxhB87Dgv9enhmrcb6HrVwIrZxDuqQEWvMAxJa4WUqofKASo6wsqt6YNE92DEHaZSw5VD5UiTHz2UV4Kq5dmVs82TFMR4T+FqwdEAIt1TVAvHs0f23y6E/14i40Zy+O4LlyPJYyC6X5glGJH3OGfMX2L5wh8b5Buu3KJJdZ5DIrjJOwkA+8Fy4WM3BmLcv617BF/wHs7P8AduE/gXXg5gj2Jp2r/+kBPI8isrlZLvfgUQ8bksstp/ca/F8HCCeadB9mg/YzDyawL6BQ/FICv/M60PQClryRwIeRKQCVc0EozzWgNqpQ8delQTIOHDpoCrVfhIebCnj1BNVVqrhqrBd7cOUA3hVHxxgH/kijwuQOPU62zbv2Jghj757WLgfiG3CirrXIKbajg8tFPElnoZPE/sls6i8iWeh+mRJIDzlEyc2/q95/ZaZbfwK96uWrNLGcVs9bVhiDfRb+/G+hyHQIVff9CoM0lrEE1RtX5D/WLkN6tNgI1F2HB9FpS1BsfBXXMuVG9SMhOHXw2YAfXWBr3gKy97RTDgzz6R9qTq9nNo8ocqC/6ZPPBcHN+QcjtLByE/ycX+OOp0kpYIGom2p9C71aTaGKKE/8LTnX8leNtBcUNiBb9V3Xjxf6INf0XdEfb/LCVG6GKN2iFd5zoXshMCfnkVGwzWPA0G/B1lVYbfTfWFgtLs/xMKeRFW2KpIIcfA092fEyv8DneED4wV5bVw0IXF6NJcjVRlZhlatNcrWFzy4DDq226j6S5J8GlD/Mf4RFOC3oYV4BqwpLIAVU4LWKejf/6F0JBG3Gbhr5zcj5Ga4B9GvOQ3gaIjxFRzidzaF+fg0LIKT/Tkj3aEj/9tVzkf5lqY409PFbH0If35+g3loMc1Gez6Isz8K7wHhRKX66IYsdSTx6R2hWx8BKM3NbZEmUnaCuWe546BSrs8RW0zAiDOi1UCP6QC575NooZ6B3yzUitIoVi9DXCh2/R4cLBx10kFP48N+Qn+YY+evPjuBRg8aE0Ru/dPKozXv3hQvQ56ORMQQdw9Zb1RuDzMDTwWajxK97gdwiDoweImcn0X5OeusMGoA8A9DBzxYdHVwmspnGUNGGyCUgfAudJn3QfU42k8CEUJ3IboFh9z6d9iDfWicopu3Qps/P0tmXyMfatV0LjG51ffH+PuJzVgDj+fPgiBKYxCpFm9Jw1D+BtWJsILUUULV/9eDnkaOsDrsyh92BB+MBoVO3248sywgZf86mQ7x4OwIeefBzLK/c5Jan8/LncRhagvuNbl7y/Iiiia6wAQV63/iz2mmNCzX7a+//u2af+erfNvuaMc2urHSrZ2KHJFWyfZEwDn1qby10GgMX+wzKcjx9eH2KQQjWGfGM2r5W8rXAI4lnyfUHZgTmNuLhGOujwHQQlo2PQqurY9foX6gpxXcmCv+6KcHHDMK/aUqt3pSwAWeivodj38lBwYL05K+eGbWolzZeSP5gTu6Iuz8tJw7MZ2xM68XLTGA1QPvDvtQaT6jCGE5egtmqh/AcCUTk4IUNq+ANwkX8f9TAfL5XDfj5bgrQjhnuoPLtuxME/pv3cFA9hoYk/t2nRhT+CzWC9sfcTxETymtRjcEJRjUpPUvmpWfJpPQsmZeeRW0IVs9XwVIMxwypSrHLTuQ1mIFavKZ5bEKznqD5RiMeNIFwi8Rv+XXcGYsDcVDb46EyLgi1pgWLqur7zq+1aWxNy3aKmAsRIMpkpOizZ1WK9qukBD0tBd2BrsTvb2lbi8Y/Jwh04BPnZe285sNQRJBsckLguPIKth11QI7rGiIcyqC7sWKiK77Nhrc40n8HSA9d8jr2u7Z5XYpnUCvmazvXhfRWRLeA0bzGv/mhCbJo3gQ0rU2HGO0ktzpw+dwvcfcEGtXqy27chy3cMwwt/JKVWlDtsJ3WHGxkB8fD22TqC/TLgU450C0HelD3jILuiXsuUg7Log25b+NZ1jKj2+29XEgQ3G6Xm9dHaWLv5I6DdIaVdQ52fa0LKEMHzL8Fs/1Iq395MGyUa3u58x0C7ufjnhxBI2kCn/qOphcMbkIp1EvUhrUlrvORGDyKR2Nro6yq32fwuLCirAE6PsSToOzQnWo9X4IGURjggWcQ4Phnqh/beHwJf4Zs289/OYyUEBs/Q0r88Qz29WliZYu5/qfYuS92a7h9f5N2IQAecsFrk+Zz163jBMAAZoU7+U+6NYwdAIfouoDmRJ2X8TKMZCIbauoYz9+AOAjk8MbYEV9CuGyz6iEGhd9/RlGDfl59Br1EovzazdQC/jfAUx30dG7ozFeItn5siA91afrTq7+MndMmHxy/flLoqRnj0MeR/+pMmhB/O6MYd7fi3j/FSRdT4wSc1n9GFdm6VArBmoXTmuX73mGON8JF+ccwIy1AT0n8Ip+3d3TVaW/1P4QUcLm8IvqAdthbA97Cqqj/O3QjXj//4a9GiEgwdA+h04OUjV9VAs7FwXTT/4zQhwwyxd0ZFrVy0Z/DkmmZRScMJXWIubRVFpmvmYMDeaF75Soe+dyX21iNbbgF21CrHbLqEGBpVSWypQNyebdvIR7mPsjPHlCUvGiFG6//A83L/8aI0pQFSKsuP2gk0RZrzyuZ0wEh/shfNV7/5i9GFPMrjs8kePwdH5/iox8fEXx8go8+fHD8pNRH+OiV0G3I0enN6gNqEfNvfwNV2an8BiyXtfMvnsAO7WaG0F3dc8MO9MmHZWUWJNFQ2PoMJasslMCTQPOh8wmQc9Ur6OfaqSwfYO1u3r8TUqx9lPJtTKk9rqyAFA8/CimoOR+AonAMtWCRrfyxL4k/oPsnciDdz4dIUAC9ZmYNdrD2bQa/C2/uMU1Gm2thqclcv5Mkh1hYKprXovGFlRrxgNnUdZEsn8Ht4pVv4QfTQk6j5OKv4pl3da2hgNbhEO2l4oOHIgH+aQ4WgsPq/qbtkwQL+l6KSnm/27t9ioD+C0b6+OGEHHUhAeUBPV38H8epbBx6vIY8LTmrikIPvjoIg4218fZfqn7Z7lgRdZdBEbX9QuBZ/thQmjB2ucu7AJ6/2ImdC0P2+xu13WkaDy8hL/1kME1Aj98oC5iYcwpONXLtMH8Op8QqMdhsWSAnQkQprt0AKlAbcuZgh36Ok2glFVxu4lYseHkuAIIeN4clA27lJpIV9wIJbsVvMkJ+/zRcMKHw8fr70ETJKfOvmkB+COiN264yT8oO/V4BfgbxAG0VgtGnqEN/O6h2qKam7z2ddgE1/Qn7f6am3/3nsWp6b8I/UdP1OyMO093GoJ1/bXCU5ucpeFNPkYo4VsErPyvoCt4Hu3UF7zrl3yt43iJ0KEj+CO+/hFbbTrMv5Z37cNvt+ePq5MWP9IHW2tCIe7U799CzWXUukHe20etBenbgLnRKKNRNZ2IP0xYozIQCzX2SshMLCIUwB2/FexsJMDb98cW/wqlP/aadrdmbnCAIi+UGTtsBn9DRIXkn5uDPGLSNdrc71HBcvb0AwV7FvRFJfgaj3H14YF1pwAyjhfUgBg1/O0OFERyX1MJCDZ1qQT2j5UkqsvIzmMS/pX5U8mo9DZZSVSPYoB5qbhtfC9wabkDKoRg6DzsgACKjEMmUzCnb1bs8FygxopSjQRTo16nSD2inFIRCSDU+OYL0wgSkVBEoA1qeSzgGCSYds1P9/LMBnLtNjW7s1dNfjM7dIIhwH4g2N8z1L+Me7gfHabSJ/IUN+jQuSqT7PnYzTYaseADaXcSSPeokpEhehKcZ/HZSQvr1Sfo5eKWs3/4CN5dFJMvlm0gNxpFqrr8Ba3zguKYQTN2gKTU1xzVV4ooNSALinURFWoQOClFVpzCa6/EMB69Vmf9iNZL/FdR+9WOabTzp5yNKrJkIjNOmWBkq54T1EqyBFMj1v9QlAU0Tn+Jriq3Lhc5Eh5UNPaohc6lWxYphbEs/tsVFekM/4t4ZUW05cfoLIl5YZfIbfYaIwQVCKnIdPxTVdBUj6+TXxSE7/2cjSkPX2Pzq1xKrCTvSlV0UFDFY9ktVR0uwNfPhz1VhZWyUsYMzPx+jnOHtdUHauBbMDR8izYRjGsFbH1PlL/UyKWLz+bapuFz0f4de0j8n7cvPkz5Xr+QFRewGoDh/7ajGJasfQyVOlChRVeM++UxV40S1GWoKN0QVDXdijXW/QDXGpUN5teteErjyxEg83CKAI1QuP4VkjyLZuxGkNorLNt731SgNrT9VJ+X8X6jaX+8pXfujL0SdjcbRxT+XDsooEgnRGNG9mujFGn8fjdXoe2JE0dqxMq7C5zbEuqbxCbXOpVqdpsZPJkOdMtUJEl69sYqb6xuwB+qOaAxeElIHGV9yROuTG0KqVqwr8TpVc+km5CiOG1bb78+h1ke+HEVm4oYRZQz3EF45T6hTOdLFiuFaDmzwY7ohopjvjWrLG+Sbdz5LIxfwTpo/78zhUzpNgmp1t4SDyEAoyMz1i1FizNRa1GOud6OAhvm/Q2vB99fD9ACz+5NqRC9fuH6EvAHVZvVIoTvVJt31dwAELPvTPL4Q9a7soxMK2arB3H9V3v4jQ3hyJ5vfdIhM/LiFgJ+1+xk6arChvj8gDSce0sz/5vpnkcVXLgTc6INuZQuZwa1IBZgUxAhy5fQJWMJqQf1EtP/7dPPAZJARofmgknPf9W7iv10TteOo/qmIR0NzXb6kXlsd5bbX6V4iTmLC/fMx2uQufK3iLMWFonqeurAy8M0U3elGei48aRJgiSZP15QCyDoOVla1P9e6CPTKBzBc2wNdhJ/NDD5HwxaXX1mfqT119cd4/8Hf0wQZ1GjL7/Hoo7l+LorRaw9rPPXpoypPNfWSOfjkm6Pm4H5eDH3BlUNaz+wF0KYPEYyQ/UMcaC/PBNCm9dQ3nv40YYGEn33lHbj3UdsL+jC8eXgLvPL/Vcvj/EEo79WPoDwX0aRaK89FiX9hAFp/SOOSUgT9WANN5LY40Cj/FYJOO0gdrCyFqB6+QhsXqD15+yBfE0e8iZ9G17tG/pvdCUDknuC+HPxcWye//Gc0Rm3N9ndVkgebk2VHN0/5WUz9G9bkxsBP9dmrDx10eOebGq5PyTCVO4aTkO1a39TIvBYiVRKjkz1/8GC81f3kozHaTYpotIvyjb/Vyc1nHozvlRcfxeVHPyw/AMzNlwDc66sht4e/8wnm9mBu92914vIkNXeai3IvGZv7eoDz8K2jGS/9rU5qfrA9PqNtbMZ/bCO5CkPF6OHfi9JKB0nVvYHogzzKO1DK1HZqRhCQaP5lfPtBjZ2WrSM6pdDSWY3s4dXrsOOwl3pVgTYHR7/IPZ/g6O8J1oFAq+r1T3CF5hTxwrdNsM7oTjZvbFkn4oBYtEEbHLCqn7dBlV+BEB8HDNnqnQdqXOOvcEQ8GkE5i6a6Hx6DQUYyPthTYOsKr9UFV1GBuWGRka7aJdSf2Ye36z/TRs+D9Oyg53F6duKzAb9QgMv0qyEjb2vHJoWa8c6ldY+M4EVmfIcatwfj/I/gJVB7SB1saFZ/ttOPJsPv7YMmv4YAhTUD2OIGxEHy8MbdOJADeciFP3gcKEyV6Kv6hRBT+AyWZG5YAZK778lEQUDQmeeB3ogxtNG5SG9nrA3fSSQ39tE27FtL3UU3HPa/MdqOl9b+y3Yk8qfRwY8ACucPmOvfxavqQyFsS6XE+xtVodSG54UbdqmqLpaCvTPYqyjTn8FIc/3DeOhWatMkPG4R+10u33j6GDx6G/CpeppL2YmVjc4A9jPm+r/jEJ2mot2IaP+jAVbtOJeo1ZE0KJiIk4q91Z+fRy1RJ5bLQUqrQCir54dKc/Qy1oCUifxI3UZeqDdeTVoMSb7r1Wz8pxat3BK9XHtr3TSg02Y1BwEZd8dy47EbPiWE3YUQ6qRh5D+BGFgInaWPtOO0gVp16KWzdIkQaCMe1YiZzCdzXBaoCW28CyfUhm3xpM2Rn8F3Xn4Y2D+EQXu732Q/7BfxVjv65GqKz4B13Mu794+hOUyOcUR/fUyiDxRXTIpi0tYxSRQ/sAtvxAcFcfXHiGCjhuA31pMuor6HQlv1Bi1Vdm7VGovnlbDBlIisuxzzUBPxzUtvjdrb3euxW/iV/wrx5H+OeOQvF0Q8kqtTz8i3REc1qYNrVez36GgDlns0TDrYuUOuiY2OTvxYBrL5J4fIvsz/Br+2ZtWuX8y9H+Mcbm3kKLF++FEaXT7di2afkixb12DHzPpW/3y0E/Wmx+xEH5GdKEp2or/qdqIo2om+5qLt3GffQAXZSV9B5D99Q7cU/U3Bg7NRtBQd7NuCI7w5nWzVODTRXksGo9fRTqSUc7fHhYaefol/lKbairQYUJGOQ4xLs+XiDYzXUYXqOoznvEHXMeJKCRQbRw9f8BkuFHpw/QvD0a0VQqr8N9AHHK1Kel3XYATpow/hLY3TPtJVZzKiVXyI6ijuRJaiEe0wGdGWmXg4jYgzU1vUoRFtJhDnOSTOzHgjmof/5ADeDonE8XCyn4wxos1EI9oP+bY03Yj2Hd2IVnsBI9qbplEjWhTK+7paNkxoMNe24A2zUVbLWTtffljdSXD7DPJ0LfNt4zXz2VY+50O9lbOwld7eC5sK3zfFWEBvZaneynNMhU+36a108Qq8zvF8U+EP+V6T1vujrURTIY9vJXTJx+NHW9kP5RWrZTu+gPDn79BpokervmCH+YZDsVauy9IyL0hV+xNaeX9v2rnbyQ1KINGXUcOc6LEzXuKPPg2z+WKjsIAOv15rO+Az3s3C8ef/AYAdbnk/odInSPiVqR2gAwf3WeQ6Ub8LQf3CqVreN/TyWIUVnSmDiy0CvyoXPzBljV2RXUk7WxblDpNcYgkk8d3aFwUat/ZlxD4yAdS1HQ0L+yDK/sbDib7UBbJk1L1iJJMsWWTJqrnHhA0I1veAeltezEZo0m2ED1yt2Qi/d9R0R2iWZWhlOhoJLWQjNN3x0Odo/RPR8ldB38YLLhJ1ZIlueLndh9clCnj1o+Fc3xQLM/4iklK40ghSHvWHf8RcUbSNCvJs/eB5vJtT2629igrlP4Mi1dKcRmbdAIX8yOhPZxMajuqFQOfdLkb+cf72/iLNa4UVi/Rp8jFb+4Szap4UJcT9JtVXJh+NkybdOPnhWXJMbqerMUV5pRHNkdZHoVlkiqwJNovVcR+WPxXD/moV++P5o9iHTBuYITIOiZDO2ogMX2j4W+QMPBqfMKJuKveNfrqswMO+BPrdj74Al7M50N0NB/wTcWChM0CavsfPt20FWccua+gK5KJHx0Kol6BVpwArZAgZN7AsSD/HL0DOAtRkA3OK1HH3jO2WcDIyDS+K20Va9WT8VjY5EVk9NoU84y3kHG/k869CV3lrTXUreWGNB+RYpbHhqH+AJbjZg/gNauiYZGSjiBG/RD2Xn00FjPVPK+jnzY4+B5LZXmIMpACJKo2RFCZBw+Wb7CViQISwXClGRJgslxrlB40S3w1lqN906Y4bJOg8pnqOieRFpvqPDffhZxy1kYEvfTco8Vv4GMWz467Frt90zha+fs1+zKtrNMI0ymSnkDRTCuuyA2ZleQG/FUuR6wrkuly8y/ew/1LkQZ+Bz1CdXdNZ+TDEptAnCKCxBDP6Nl2ui4+Q66bX
*/