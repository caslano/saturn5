//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_GET_IO_CONTEXT_HPP
#define BOOST_BEAST_DETAIL_GET_IO_CONTEXT_HPP

#include <boost/beast/core/stream_traits.hpp>
#ifdef BOOST_ASIO_NO_TS_EXECUTORS
#include <boost/asio/execution.hpp>
#endif
#include <boost/asio/executor.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/strand.hpp>
#include <memory>
#include <type_traits>

namespace boost {
namespace beast {
namespace detail {

//------------------------------------------------------------------------------

inline
net::io_context*
get_io_context(net::io_context& ioc)
{
    return std::addressof(ioc);
}

inline
net::io_context*
get_io_context(net::io_context::executor_type const& ex)
{
    return std::addressof(net::query(ex, net::execution::context));
}

inline
net::io_context*
get_io_context(net::strand<
    net::io_context::executor_type> const& ex)
{
    return get_io_context(ex.get_inner_executor());
}

template<class Executor>
net::io_context*
get_io_context(net::strand<Executor> const& ex)
{
    return get_io_context(ex.get_inner_executor());
}

template<
    class T,
    class = typename std::enable_if<
        std::is_same<T, net::executor>::value || std::is_same<T, net::any_io_executor>::value>::type>
net::io_context*
get_io_context(T const& ex)
{
    auto p = ex.template target<typename
        net::io_context::executor_type>();
    if(! p)
        return nullptr;
    return get_io_context(*p);
}

inline
net::io_context*
get_io_context(...)
{
    return nullptr;
}

//------------------------------------------------------------------------------

template<class T>
net::io_context*
get_io_context_impl(T& t, std::true_type)
{
    return get_io_context(
        t.get_executor());
}

template<class T>
net::io_context*
get_io_context_impl(T const&, std::false_type)
{
    return nullptr;
}

// Returns the io_context*, or nullptr, for any object.
template<class T>
net::io_context*
get_io_context(T& t)
{
    return get_io_context_impl(t,
        has_get_executor<T>{});
}

} // detail
} // beast
} // boost

#endif

/* get_io_context.hpp
h9kfHhleYrUkketU/ZM4M5hXsUx5VpvPtRo1QnU5J+fcT8I0ycM7p2tmo6GNig7GT2445rk1rMDmwJOQP1ZVE2gTPLXQ/gfkc7vpobf8ZyvB4y2PmymsYVHEryBJscJefXd2lr3i1pvv9BuZ9MvfoS/PsB94ANEvNMISk+h2h/2hpNoAnhPaZ/neAKn3suoM/njDZazBfrUkPkEer1w4wSCC76TUS+DNPNSHT5zmJObzk4WG2/JtEVijm/Vf9Q/3xCd35K+ySa7IjiDfZ/aevoCHn7jmbzAThNli85cVrE2weRLkzy8h7VHVHMhgL8OD3xICbajgFOmXj0czPxEa9WdtLw/dBeB+Pv/gDfmHcm59lB807pm3Q4h8C8mHJvvAqW8h7zFklbv4mcBhEHUX/gQ+vnG9nIYoNwkYVkLdne+30KO6VGiSRqW+Bovqqb0miSreIGRRscKtAGQ/KpxLboN82f1O8r35NkbemYjXHWSVifitAHH/wmVe73Z81HsA/6Gf+ZqRkN+kHRi1ENr+B4z+uG0DX7tgBdR4yGcP0NNxjdj8FV/PeyHgHbwRGt4juB8l+/rC1a9CTNuo5Y+N0DW0sakqp7SH6S2WXzHhKIVzHIktj/pHfoQCsnVXwod7pr/C3pbLwakzoXF31lSpNN2o8eXyckXuzsWYhfCVHTFXo1d2rAE211S+XhjNfn079t2XWK9VDecGjlorsORaehz4hoG73wB/uJr72DiH/Mp5pw/P2DtokViygxMUxttQsu4AVOscyQhEERSnIwkNBtMi1Zlxfq+jpYWx38RbFXcmT6G6uubfdEenXOY7ScrOIVS7BInoezGfVTF2prtxqk4e6i2jBIzFWCpv2M4cRisRUPLT4V4i4GF+TNz/iJ5fwWJH3bu7Ozg4SWG8Iyfo2kO0gZCMcxVDyjh2W95eJuiGQ7SdkIwx63MPpDQYRGPK94+6TPaUVVeskzC83ovOiS/4Yax73ervWKciOa1EgMnLEgPk1ddLChwmxYxsyC7oMeOrFmUCsZfIxacA7asAw3McQFAZAij3xbQ98G5/nILQ8hvQayNQb8PlMJbK3GcLYCkrHnsocc1QhZbuHy0Oo6bfdqSpIzIv7ymAHnveuzJzbwMk1kDc78k8tbzlbeSpuHMF3I9iCLmM4WkEYu9bbtWxMkeU1v9pYOXKiE7s2hwafPpdO95zY8hId/YTzfzeF+ynpN5fh3nTLmeWFob9TLeRGgKtL4sP9AlqoieTsxeEsksXi6OdOLFjBtvn319SA80OhDgyC9QO80xnJ/wnvc/A1RLszjfkyp+Y5Td5Hs7yEfLiYEvkvxt0Y8BZRLk28GYmdmPgQaqUsiV/UM/dLiLR5wyO5mLBG6xZMdLAH9XOYBfEF5VQ+OhGoiVN4M4AEizt07NBf01K8o644zx3FyNilbfZrV4sgE3Zh7OSlRYNGbruVf04T/HfD81gFjseZZH6KMy7oJZwZ55w4jIYD75eOThs4mz2HVRSNfenoKK0jwafR3QsKhlPmkWm59sM7yufn3brwHXkuR2cGwej8TgmjehVtsr5DbgQLes2rFo4Nm1bv0TLPS5Gs5GmlHyT5e3NbCWCzrcMs3n9c4ZZ2vQ4ZSfpqft3tB177AynJAa0GjTq1cy3HmgIvj47BvNC0upFKXsJIn1oEPCnRDHHwVIcVPf9fH7KaFcKelfKd0Q9yyXm74dt9enTqv/Nz2DH8CBXY9SOgQFkh/64Znb8q6VTyacy+NjZMhTwOzt4NkpZ2Qtyvw8ucSRs1LRyGmzDC8cCbFSuasQNWWvALvdAEZGS08vKf2nNuCF1SMhi/3WEaVPJ8YaTfJT/5wyu/QCstsNgtNet9Y2ThTFMMK4iccc00BZOddFLAMFL3hbJ+AODXIhJsg4FPiv7k0hmEcvw04r8H5Fdn6BG91gixxLIBKP8kJ+6AWpMWOdkpRWwRwLszrXSyJEUIkxYbA7T01Z4j3HaZj66BNONXzprou3MaXaGIzDabNjg23+UfArxIrz0rzH+UuME2UH/WYBOTgNPZLR8z4x4f4hvcFqzGM+Yx+tc7cRDC+euoVIuKgHigNVKWwZi1Algg5m5uL3ezCPmCWyyp3El+fJfRLvBeY6sRSJhKhT/B19agKdq2rFFEdtQp9kLNWpFmUAa4gTUZlZFj8nBm6GAmkQfR5BwdQ5UC6m/w42T6EL87qPZu47VgyXN7TOD56su8GHC1zYrszUryf2vdAeJGo62VAxoK2xVOj/K2KgIBlkm3wHe5+hK3QfwCWFhhlviKcEB0XlVVwj1IUcDehn2xBVlK39R/pebFG0eVxDXET9q51aTW3hovTtTJ3L8SF084p0ngb9RobGlp7/Tp0DaMjpZWy99o9rr1nGiDaML/Le4ptdUL4BhMsh8XuqXjoxCrW/jVWXQW2fjx5/pWNqHVTMJrAvggjpYHOUwFw04cr8zF0ATAHOAZQtR15+jUc+UWrNvEcC3r/1fJ/h3oTEcb8ve6NqIQRQnzfgU8s2svzgJ4LiF7CkEyBnBgilZOqGstWslVQfwOnYXwIOPb/C/V9qVHvyZdrd1rNEetjK003qeUspxDyn+FHIBbApU8t6uZ8GuEfoF9wynUsl5iBkf9ufpz9Vby3sy/p4qmWybQyvmln9dwdZKnGFNiYY4xRSvBj8Q7osoA1Fzrs8tkW5BKq3niEGirolSSCsLc67SOe3tbRFF2gDBuQ7w51tuqIcbs+zr3kEs8xbyz8H7sHgGIhTNzLcpB/5lsng1zshgOshfSZ/2DEB7gPCn8V/0Hakgtgw1ocFn3gHhApzF+BkCAqH0G8nSwPfKF4/yIRICCsCOy/9gfTdJtJFbMTnvYC6xOB+9i4/Hn7ooXZvsD/r8TQp4kGTNiNnlbQ+XrmF4giHHoyAaH90ZUWLELOZlegNGgzd6lm8SRPKO3qPTCnX1M1gy3LBAABpxbHycS3qhSPzB+/kBwbay7nyX6J5h8sN+oFjxIcqFqzbA4nOQuwnBcMigQPpA/QHLd2aK68zAtqhCMXdFlzJmp2HQC6Q/EbxeX9Z7pZra9x/xLqtCuQU6j7h+15iEJJTXrqHZtUDq/Fni/BC62Z1L80znhb99segF8RVvseBgb8rIIcKbWRfyZFjDgiePFlSYd5IqCvUye1CcpJBFtxlG36ORIU5VCavmMnAQWGQyJ2+LSZmQUkQtS25VlkNH67OOeE6S9Qm5Exsg7Utvh4LhwQ+ZsnY9GoAWFCZP03UAYvHcbCsLJ3+YaZD63emp3jErg+P4kZepIyQHkxLJnz+TagN3BHldo4E/jbPJgk5o8zC1ZSSfcu6eVUkWG00XG1EX5x5MUXMnuWzJh9t5/llQQhk8ykB5BRNbv7NNkViSlvebzm2Y1m8eM1b5JmpknnPU/LwIy/zHg70YvV1fx2bFNjtbX80PEFJN0fwQqVlvyaT49qDQFnNz2Q7s+bLsz0FOF+d4VWrW8UROL6FUTP+PlqV4QM+2tmubhmCm5BVsZ3NiFyViOgRWgcPKLO0yiJ0OMAWApI9qz3ACEMfzVAHcrbzF0B/CAIcDCB5UYarrFLQr4eSAT82O9aEG00sv4lD2ZZq2njno2KWnUv037Z0+md3U0UUNzZt2xjb7NYmMWpFi15yx5/RHY/W2zr3bFZAyWcW5yDbGCTLSmohLbff7X5pSUpvG6D9ODOLpK9HuaSQGTjAsmnRIBOpMlTWZ2CiobtrClZC8lSwnbwqG88I6BdzHHroHG6OYud1rMQNa6th0hv657TDjaTcVpnord6yQ1UybpSLH6ej6D++Cp/lwKnpG4x+vxpWag7bAdIfB1fn2dB7XDctY1QKTornElmMM+QUfoyaJg0T5QtN3NR/ZdXrI4Qdumk9mCMSLFLZViKB3p7wAyuSM1C62WGMQGtHrwBcFo9fRkSlm/mkVTgxuhaZG+3k18jl4fn34ekyrX5pRaleBw9z8ySe+5WPRYkZhM0JhJNQgnJIph6sGeqHH7tRKdErX5Dh9VdDxNIebwoNZW8owMixUVIL4uODhJnQXZPZoBRdtd0TDoZgZqdXVcqRXlfAZ37sAJCjUrkKZ/VcPOSG+5z3ccyJRnrr1iFgZFzYd5o7pf8UwOVuFT5kjJvSUimQ9X4UcQTWbjHSUk1/XVM4NOCU1dNzjwVkLlnuftZm04mwzRVPtk4k+9dKSGHZuvYU5K4EpMvWoKw2BVhhxeLNEZdeQ2+ozm1gW0kfsi0AjJrmHffRZVbFYQkcgnDhmaYneQTZKQPpnmPHhcknPqEDE5unFICZsw1ku+LWrte5MMj5IqkoKflv5s6VVPbcg6vwqmu11woX86vq1+jjYfIzWL//NGO9MGXBEG5uN0BorufZt0BpLhXWbQQSqoV83htH0n+qhf+93nbX7IrbU8PqOBKshcus9couVRb8mHPrgFK+Z4c9ahkW9BHFm3o6ETAtlZel632Loox+WZuzHwjE09JfFceq45LDkT2Z6QWpoj62ueSB4RA+ZdOEZLStngMynNk0Fpme4NZ9+meNeo+hv6kaLqc7His9PYt6pnzQ1q7xHbdWokdiWZIP+pcdX/JYubU1ytxm8i0WpbiNWCLgbe7KapkGbOwEDVoSIXC04z8lpuy6vDD6LmCogH8MKYHXb+cC3lNv2NTGp1aMXn6H1As791c/p4q3+GHJ/xlMkiABXig5Ug0YnRkdEa3T6UEd1YK8+ukpHNnSzVdsf1HoK5B7zWlypRY3l+XjtUS1UwddrZfR3AU2Pw+6t0phx+8Mj2cxHKSl4auoKWd4hsbjOCERj5zceas0huDlX5YiehdyOZq/0Nw3l7hEWXr/p/svYykNIfcL8HewjP/fTZWLG8fzllKoy9zz7bPkQ/uTREBkKhnhG3ODOMy5uxvRntpp/HN6p9xTleIlskq2fI97OxJI8ypcM3MXDVRKQs6xA2g1RHT+OREt5wxY5t4bvd5/afgLmBeFpGTkVTVFJGQm0VDSm9l8oKcAigIVvuQgIBuhBpm0a65sR2O3pigzhj47+Al0GcHAU6cgD04CGoI7zQQJP0fwZ69yKDArhfZEMRQqNzW4Nbv+a3fIRlEMUxrAzNNZ90jDXj69l/WihYIAEBXUMKECmhgehAr9UkhOTuiuqIjCrq3tpJ3DU+utEISG/S7r39DerrI5Nxfr7+2uN7G+F7nXrBn7WZrZyD8TzDCwddQEZ0FVEcIb6CaES/AUIiHQKE7sSsw0QIcjJ0yDI4yhUwoUAqAiJBogHJoeJR6Zhj48AIqScopyiwqOcpCQeBDjbCIU+rqxy4cyutKjMTq4yOwyg4KDq+TqzM3JCokhBUaCsN2aJofx1BQDIonc7gYFAeqLq1/AAQIwA/e+M6h2AAXagQQEQ6QEFUNQB7n6UARCAMQGGvEEBjPYB/eGXAQRsoAAQRqEAhlJAAPKygP1F3f17vcxm6MTk6PDkzE7KEdaID8RKSlIUkotVkdJMQJvu8xdqa2Nii37M0pOjaaayKTn8osfjcsMx2zHW17S/uMqzezOAX2pd6/tN0lqYXFaOP3xnZ7d/FSfqWh2+PaPCk6LKu8NuXgXDHBQFDIKIzexPjcxOD2T6v4uUPJiVqYt6GRWZnAI1v7aoUJnNvdTJkTWoPXxtj1+h/GriPlc/fDE9EeA7i1NiojKQO4thbTIjsjLWsjK/Pzh4zGyX3w//jvKTCFxM2+5/u5RU4XpK+wEK/nd6q5Ewzg2E8HQHOmJZB9+rOTMH7J+yPRE6SLixdgeTPhG44b7la4r6X9WtflLWhBBWT3paScSdzRmWRW3zlyzak/esPLz/ZDT4fTZhklRN13+CCeB5OI1d46qRW5DtF/bbthyHzwWlhGiwiSnDFCJp2eOYnK9v/ps1TtoAUe7RrTujuNCmFQsQy4gu0ThnOpoBixTOoREj7BVtKkNwgbPC9+DeCGPGnbjaeGgTLglZ1gS263jJw6teYeAFAuPkrrnGca6CGndk7TxpCfZwo6nMgo6OoK0zfqU+X8dPF+M8R5s+s9VCLT25RepNOS6NGnDMjYEELIwayfykco5tnPb0LHutdTZ/91KpvLqnruInmz6M1eShjMV8+BcDfacb/X02HdDGkz1tUsgS7afPiFyZvZ0At5pmOzc7O7RscVd7cm8FfW0kMy9k9EZcsy3acKlQ+LMCdfbEfBl4snoXNeF8o/DqopwF6WOsKy8WmDocvrbCtdsc3gCKNP8aTXEA7dqoNQWmGTRKgoY/cTPliblY00Dz/8daU/muu+KWV7Tho3Wvr1Ghndya+rGiZ2A2os2W1qtEoAWrzZzh3QcwZKUPTGldC9DsKkNlP5Kb+7JyHGdlVhrFQnHylqfvZG/TnsUJyVQGB75LLceBV2yulOHGPhByap9YBhpSL0EDdRYq4rc99eKGHfTKa+wXk2A2YZqLdd/NSEVcu9g7yKX6gGauwTKnVi/T4npwEZIvRMr4LlJihc2v3a1KG5HllgTwtsysne8iol1vqcMwLO9YOkS2A+SsjjTeGbjs+KIAafOLdBBi7RYp4+I97c4AP3xqkNTG1TlxIAj1qVZa7TbNUKgBc8s9cCKqJVBu5wuIhwa9LDXzd87XI4oy3ttkZ81WB94mAhtaswLXJmqI3ylWbVVcvwEVHEWn0QfZt6ANJZV5GnOa4Odx0M2g0hPkphlzk2Wm1i9onFbLpj4Nsfc4rxu+f39/gegBAID/gPwB/QP2B/wPxB/IP1B/oP/A/IH9A/cH/g/CH8Q/SH+Q/6D8Qf2D9gf9D8YfzD9Yf7D/4PzB/YP3B/8PwR/CP0R/iP+Q/CH9Q/aH/A/FH8o/VH+o/9D8of1D94f+D8Mfxj9Mf5j/sPxh/cP2h/0Pxx/OP1x/uP/w/OH9w/eH/4/AH8E/Qn+E/4j8Ef0j9kf8j8QfyT9Sf6T/yPyR/SP3R/6Pwh/FP0p/lP+o/FH9o/ZH/Y/GH80/Wn+0/+j80f2j90f/j8Efwz9Gf4z/mPwx/WP2x/yPxR/LP1Z/rP/Y/LH9Y/fH/o/DH8c/Tn+c//z3x+WP6x+3P+5/PP54/vH64/3H54/vH/8//9977r2SHUG1eR5ePaBvriC7NJZRtluuh16Pt/dPD7/H+09XNNojtxavZ9v3u4/ksvsSsNHdGjqe3h5LJDw6pUq6ejfo1FQl0EEOG1NXR6eQblMhoV10e2RVZnRd17WJwVqzk/2/iob2MhP5gxLxjcK7Yr6qxOJrZXYA1PnZQBsO9PEN++v7S/8s6FdzW+byQu7sqqpunHb7EGe0Jlqjk50ylT10ZYt7dd1Th6OwRmVsfFt8YWBiNEJnd2JmalRKRPoxGUlAV/qy6Hk3aSUo2N8/OVhraQolLdy2VjJdTUOja0A9X3c5vP20zbQXEH1kvDYB/dWTOLi2jSMA4x8dHh4c7h8dHBwcGBgdGRoU6/rLh7UvbCODo0TkxKREhIQEhcXmCUWFZoWEBIYnhoaAAcZ69NQVqAAHyCYHMfoq5E9BQWHxOg8xNw/JQSFJwfkzubqNDYDG5I/YBwVfDNRnCLjf4O/GC7CFL/tdBY1ZOuJx16rV50Z7h2/V8KPHDS0QBD5gFTAKBAH8sPPFBn9ud3JrBnN7
*/