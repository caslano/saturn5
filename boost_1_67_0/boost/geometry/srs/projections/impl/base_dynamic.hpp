// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018, 2019.
// Modifications copyright (c) 2017-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_BASE_DYNAMIC_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_BASE_DYNAMIC_HPP

#include <string>

#include <boost/geometry/srs/projections/exception.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>

namespace boost { namespace geometry { namespace projections
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

/*!
    \brief projection virtual base class
    \details class containing virtual methods
    \ingroup projection
    \tparam CT calculation type
    \tparam P parameters type
*/
template <typename CT, typename P>
class dynamic_wrapper_b
{
public :
    dynamic_wrapper_b(P const& par)
        : m_par(par)
    {}

    virtual ~dynamic_wrapper_b() {}

    /// Forward projection using lon / lat and x / y separately
    virtual void fwd(P const& par, CT const& lp_lon, CT const& lp_lat, CT& xy_x, CT& xy_y) const = 0;

    /// Inverse projection using x / y and lon / lat
    virtual void inv(P const& par, CT const& xy_x, CT const& xy_y, CT& lp_lon, CT& lp_lat) const = 0;

    /// Forward projection, from Latitude-Longitude to Cartesian
    template <typename LL, typename XY>
    inline bool forward(LL const& lp, XY& xy) const
    {
        try
        {
            pj_fwd(*this, m_par, lp, xy);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    /// Inverse projection, from Cartesian to Latitude-Longitude
    template <typename LL, typename XY>
    inline bool inverse(XY const& xy, LL& lp) const
    {
        try
        {
            pj_inv(*this, m_par, xy, lp);
            return true;
        }
        catch (projection_not_invertible_exception &)
        {
            BOOST_RETHROW
        }
        catch (...)
        {
            return false;
        }
    }

    /// Returns name of projection
    std::string name() const { return m_par.id.name; }

    /// Returns parameters of projection
    P const& params() const { return m_par; }

    /// Returns mutable parameters of projection
    P& mutable_params() { return m_par; }

protected:
    P m_par;
};

// Forward
template <typename Prj, typename CT, typename P>
class dynamic_wrapper_f
    : public dynamic_wrapper_b<CT, P>
    , protected Prj
{
    typedef dynamic_wrapper_b<CT, P> base_t;

public:
    template <typename Params>
    dynamic_wrapper_f(Params const& params, P const& par)
        : base_t(par)
        , Prj(params, this->m_par) // prj can modify parameters
    {}

    template <typename Params, typename P3>
    dynamic_wrapper_f(Params const& params, P const& par, P3 const& p3)
        : base_t(par)
        , Prj(params, this->m_par, p3) // prj can modify parameters
    {}

    virtual void fwd(P const& par, CT const& lp_lon, CT const& lp_lat, CT& xy_x, CT& xy_y) const
    {
        prj().fwd(par, lp_lon, lp_lat, xy_x, xy_y);
    }

    virtual void inv(P const& , CT const& , CT const& , CT& , CT& ) const
    {
        BOOST_THROW_EXCEPTION(projection_not_invertible_exception(this->name()));
    }

protected:
    Prj const& prj() const { return *this; }
};

// Forward/inverse
template <typename Prj, typename CT, typename P>
class dynamic_wrapper_fi : public dynamic_wrapper_f<Prj, CT, P>
{
    typedef dynamic_wrapper_f<Prj, CT, P> base_t;

public:
    template <typename Params>
    dynamic_wrapper_fi(Params const& params, P const& par)
        : base_t(params, par)
    {}

    template <typename Params, typename P3>
    dynamic_wrapper_fi(Params const& params, P const& par, P3 const& p3)
        : base_t(params, par, p3)
    {}
    
    virtual void inv(P const& par, CT const& xy_x, CT const& xy_y, CT& lp_lon, CT& lp_lat) const
    {
        this->prj().inv(par, xy_x, xy_y, lp_lon, lp_lat);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_BASE_DYNAMIC_HPP

/* base_dynamic.hpp
1d9cnB/7g6ZzvRoGrCm8JSB+iW8etTXyJbTBp3h9fjLVsk2TVabXyqNONQ0Lwn6V3xmxww6TIA7vLEDDKEKNZTr5UQEQwwNfaTJ/O+iKoRlI8PgEo8MfVvZulXP9JRn1rOCYMIs189M4y28OBHx8RcymV6mbciQGtuL95KVXCltiy+cJNlXt48UV1L4oRY/0QHLEtHonppN6bpsADhoyp8C3sdDF7jDi9B+srKeTgfXxtfmN+wtZzmpT8WB93GjXvEVaTitX1wuVq/1ND9fkRsvzmeGFY+Cw8dd1quBwmKAD97CR97+P+3jblQ2vFKfa2eaxuS59iqPJsQHgfH2RHNwu6JfkN7rVxCGh1tXpIc8paKumjzXXPV43U9s4RXs2QY1QFy5JgWUXLimETIIVxM1gtqRIl7wtm7ZHJIgksCGww50pQUOekterZF7vjIxsYs7GC3PEx/KHZHP/KJJtd1iSD4YXuWMOomqLObfkl9v7moiDSD/cVT1ZTNqRW7GaJUjJFRt/e5ZNgZR+W9U3US1w2u5n9cLAq1gXBjm81AqHdhWRiYg3nCL81CPNGubwanlv9MckTVbkLfI2JStUKYcwPndMH/9baofyTKl/PbcMm0pJVeFULJ0lmVTTX+54TYhlJIofp1zD/pFaB65LIZbX0AM25FfXVBypi4sC9qlSEwHlPWrY7rGijEvVNF0om+LG4Ztxm7dYq1gUcHkn3psP2lUt/W9wbh2R2TaTe9pX7rgDUZ/8Wswpoj4tpUfNmdUtcL1lhbEKUBhonpAHgvn+f4HeZ3iPlkTyvezrX6I3Zj1vdNVg5qsn5jos4+aVtKeaevnCnUWrRumrukFE71fCXbcJlZ3tUWp19wkaIoQq6AiFJQ4jkSJvmV90PNp7vTh1K8Ax5/TpEPBYMXl4jZ9TKQ/lYyfC6qaLYYk+HRmDOAXZFg71flRzbAdJcFj+IMqygSuEkdEa4zjBY4TDPTpihxIIQH4Onoi2ArO9jiKtQvhupQX2RuwvdOyyHJCe4ulzORd+MyjgvOVkeNnutpkJVDvQ6ACvkQR0RM9LizpXKRp+LPvW7c0EM+Y1KnG/meZMXxDahxmj7iPwoLWp9oB9iGkiN5OubJD8/zGQG17/LF1oN5wFjos6rqPbI3Ym3GFI/twoKjqcy03Lq2fdYK92MPs+e/QWbThZsGoWCd6Olm/g5EfK89SCvzNMy5d2zmcmlbscqU2wcdOAEQrHkNJb9MXZUfn+2lwpeWVPc4j2lGiQymJpusASc2yzDYQ+QG9gf5477ehF2M380tRTabn1p+hMpwbutJUOXg5DLXGI8qBce5K1mtAwDVZuPdhz4DlE4mWW2etNJeaRIflKPmmrSky0PRoCs1xscMVEvRSS1aaRdYFoTuATiGXmRA63LjsH7T8AF4Dof7BCyiMepzvpXWGnuxq6E7cK3tyov1Qo7pHVxa9ks+KP3FhkYWc5FXT+D/Q8pnfvfD3l3fv36pR3r8THPQULOtfcaORYKcU3gaIxXx92mcgIei6G3cyH1kMR+tMR3WNPfK35+vanZ5pxaCdq9cg1SEt1FchMZASRdvGKDuR98CLqZ8IFTeHTsmA4DSAkng/K2ACOtFgCRBqNHN8Y054SEC161Br5ARGGIWUotD9Gfa1EjlUabq2+bIggTktXJyUuFvtLICfJJ2JHCZOuHL4tF7evsFsMuoWM2auQouT86LZN9Ne9fITnkRoraKXnkZX4ixTaU8bOwV7oi04Zj4uqydvG0V8hHrNbtpXMpatPcTWpjK6O4qp8Hl29j6uKIF3FcbUslOfu3EpXcu1TV2QjS56xczISv4P2eauYcS/yUjtMgoog0Px15EldtH+vZ0q9cTM10R0MD5mv7Qmpw5ZTWYgFyKZMVMaKe3EZWoelA5wIL3ubUC/Teh1JfvgqdPwTaNpBTlRuf2HiBc+UzVCaZNOzT5bbLWUVyDVCN6vaB/SK6upqSwWPFSxbRUlJiaWCB/wj3MbjcUsFj/oi3NL/lu0Yeplw0XVoNwYfErAdj/IAiBhDnR2dsgHJUz4RkZzjmWvp8viC3oTt+Lze477ev3Z+1n6ycfpDv6DrUtotjuePFdUEPr5lqKPkrmQJOoOSW5Ml6A9KfmqWaAdw603eHsbt+McQtWFqsX5L57cDxkoxJjzy02QHw0N+pr0fccheJjI+iX8SP/5/n7Uf/wRdHN02rP62ke62zGXTaSk/cpRWf7N2JJFxvJUTkKkBe+I8UTjAERnmmFnJeNLUEntaihanyBrQWZ6vZd/k3CCi4jQp2TxniWJEOcnehaEnroj22ukag05cEO3NoGsMN+HaBbBHe22RzF0AOqJV6kvttNkWxXxETdtr7DgVq4CYE8I/PmqTeSNoi3l9nd2CejTr++7CItmfypFYvL9U8+cVx6mRCo7cn8OZ6w7AusMGM2EiuQhRfVVIW2bXpjkK9xW+G8545pZTZ8ps39q6tWlOVenV7rFTedP8Z06dlrm+8QjtQPmgIJme+PsAROlbkl/W9iBgrF0tcaolBLBcWilNlulEV5umOkaAnpbkLRgUxAPPxIJnMpJBPLKWn0XotFKehIBDv9GpTiN+T/yIqifjYxh7wFy08yBwdkmBBfS9yYoiInpNVnyj8/TTGcmpQz6TGZy9GHH3LwthTIAkiCdo9JjhUBr06qPaLoVNSp9FOb4I5VuojYUGP1DKOaXtFt74JyProEP86F/IrNRX/MGp+xzaDfbY5DWJPKK4nhlOhFhxBMVPszjb+DmxKod2LTENXxCdAPRoLDPgKqRmCwcb7k5NfJXcBq5O2wbEb86CTpmRLySkFKYShgSLzkoY4kLCkIDDzBhyQqtyMxu77FVifxY5wm5QfeXNHIu6yEGQ0aaiKuI/Nzr1GU7NomYj0tktHFoi0vAL7Juft8t9s6s4DqbOIfmNTHEZNYmjvpjPwbC85nqsksjDZWVlOBEdJS4hkPbqkbug3YdmtU/8ckq/XlaB3JRQ6EKnF/NXM58xp4GNAGLzqtWqAs06h89VAg56rC4s4BrfvM0q7JXUzBX/geOHxGiNeIY/boTo2BVdXGBpyP3W7t5bHBdHqccg1v52sSztcTEeJz7T/G3i52e/Zeytt/dZgowb99gxLFpwi6fxqM7TYTwCLDHKP+/XTYVUKlpNKY49tBvygqdakMDnwEZr5Cb9Aaf4w1ZorzwznZF7SU7wzHTcH9Zm2pFEZcLKRF4YjuoZw7MtCJpjJ3b05LBsdgk9qXToSFHh8M503HsocY1YvhW6WJJFCmF26KCqB4bxa9TlMrGbrrl3h8WNs3X9ZhLLVIfyPwbeVYDbbtiAGXV9Jme0A1zp450yKGYVVCM43vDRbmwvxjFhu0qgWjSVATAE59sMAPHOdmYWhTj+izPEcUJDQ3fQFU9eckYPECPcdSmCJKJKmKoIVb7QJTbRXfGxG4JSzSeGoXqoovx/oeUkjOk2XusSxVQxBG2NPZwRoguLJY6UZKM2XQomXFXaowO6dLuntnawSiLH249XCLcIsXYEYnySBv8VcRIHAT4MNvYkH8WWGxhmB4ZxPbG+nuvIO3VZAb/4EJ+ayObf8gJB2wBfYLLwgzUi3qxbLRJ/WwzuV0AV81dc7k1cg4hgfXWQHgyoUeOMbQ09wDZ+U7yWeu9Pi6EYEud/amDuUbHr+94+ibcTcc3fItb929ZNP/F/tmGaac2OQZCZyBhtNQKzeA+QYCUDF6nrUKDyYw9fK54KzKfw3m86lsP590AkW0x9zGYBsoP9pAW+tQN7YbO6Am+J0jU2iyYvy48nFTzEdp4QHAoDIZ8KHtkHbYd52I6Ef0+tsjEreUBMoNYNspPMaRgMCfsSIm/QxJZqzfrjUJ9rRbSNvZCHxDhjcunXBsIOKmQ7Jj4+RZ9yaAG7bR4Cy9kO2E7Y/qUusy9Si+QSaIh/OtptahscFbgTo49YIeCoVnoDHF7Y+sgemDKKi5Y7LHv1NxCzR6z6sk+XjD0S1a3nMCxWJQcS9EJ9PeQ3ogJm9p+Qto0zyvh7ieH+TVnxseANWhNdRrSlDu067RDQ54q/Z0OzA0fP3mgDmC5LxA7qY+S1juQTicngSrkRHCmc/AbXIyPYgzK0vdq5rFd6Yg9R71KOnwWi69DnuKM3F+hE8WMLb1mEIYuHN/QhoRFnZwTjjpxV+hrE+5H8LCRd/W3EMhIv/a2PqYurZjU0icYhxwkYYx4CY4FMlJyAJ3GflNQ/GvwIAS4T5VIG3z74EexvE1MqFu+C/GY8Uv5WsWMr3a8x79+pmDU71y2qX2GdwzCpO+dIQEC8RalwUpgEqR9SHJ4VcK1SLpDmutI2dU0bTWzoFUNVYg/bEhlhe3mAbSgd+qip4zhzdpI5eQPTFaLtBBmkxmjLHNo1REJrvs62eJHigMjw3/B5vCGKXuzD1nNChvl8CXEHLNFdQGxL5NJQbDWMcEXdFcyJDdHcYSsh7hy7UUP5bNHCFBrlS9Piy8Pg5u8qIiBsBbJRH0YGxfkdrEgeQg+bRSk9NNELbIC2Am7Soe0INwIY4Ajsmo8yLDo3gERTx/4X2hBOgzV7Y7+ZBssrQx0iBsMrlm7W5zDU8nA8nh3OKD5J2EAVeqTuzRlEiEj4TnycIdNjmUcuj5QUAGYBcWt+P4dOM9bJbfRZE4PPRZp2ngoawaaXOWRixlTans3wmWmBa805KNYT+TwLP9BKHJpVuyY2r2uOHnBqvp5CX5etl6ainXY1YlGK/7JQjKnLsezfK557wcTwwcFwg8Vx7QT0eLBgTAtirmVByyWDVNHumkfQD8MDorXKTpQbctYtdGvz9djopZl52uo2BOza83AGR/pEyQqcNdmm2W2IUNStzszXtsJ4w7uP6uzDrjszX+pDH9ogTRVS9FBOkfB+kZyf119Kzg9YRzlFTjgTbY2zgfidV9A6HLNMRlUYxcpBl/Hsw+hL+Guhdwv5wWXabyOg8TMKIiMD8lUcUOpvo5Sqv4y/KUobTHbo1c/RoQ2l1KELXzIWziiSHYjsOjOkSwFROsRcMhDRmPF7U+99WWe8l0t4zy42zVhuj4/H2aiNeKWkAG28e03q3Vf/zbvjBr9rrJy1cu2P1g55VrBe0hEQP/xhv57IpKeBxUSLz/rSwfYkuKfyl8B6wcim2mpk47SatIO7c4HZnaEMgj9thpp+3GfYPKz6+gLOd8vrsFHaXF2YgvVIfSsHoRu1mCYs+hKuLWkdinaNTaFoKDyCiO+oCfTmktr4g9AJsifxb7G8y3A4sk851yDOQzAEGWDopg9IwEGk0QXg12R4UX3U5CtkrNNBQVBHOS4fyeGTJKOOHMsdOGGnV0QIaUsaFlksMva6jLwcGeJRhIwghDCct/CpxSLx5gtYaoNztopnkVWQCcjUQalaOTjkCTFzody8e5Obd7g4tgwW0kR/bdmLVF5G0bhLXYHVo67AOiOh6wVEVeVtEzErcVLxYI/cmCJ3BOXG89CLxvwM09whE0cTNwWldnjB2U+h60z8MCh3puuMp8qIoNyPfnR2dTvmt3XRQm3vLeZR1Xx7MFR7jLpS9BwEB4dWRL35lphQ2nhKHcV67QeRc2hXplJl6Mxo3O79173fJj7Qqhy1MFS4ERnhSFY8cb33yH0jYvY/aJOo3HE9Kh6591u0RxzIJC2LuJAZJBa4Fy1UrSkFPpRQHLXzfdjX9rqxK4RtwrkBLKsjLecjeJ+gVsTag2VOku0K/xUq3BeYExSHr+zXZcpoYg6/hAzQ+oGhDRW7DvURU96UtQpK0V0caPEidZGdBER1kVNdh1lR1/EMrevgX8G/XfyL0MUkmPO+BzPxdT1cDL9ZMbmecGs1mCkW4Bx3UEfZNEdduGzlwojKBynqOo6TuA6+M+o6eNYuUdchRKOAHVNsBT4ZUNdt4EocB45xOnxb+LayspC6bhM/qOdf9mZex2Ef13FMxnW8H67bzL8N/DI2/+hq9E+PrkZndXXdDn4e518sWHXh8iZmK6xctIy7lof9Yp9Y9gH420eAuntTVINJy9/WD6YaK5kvNHnIkrY+XSY7BwsQ40L9miTdODfcjbv1dPcKPZHKxIV7k3wlEqopudECY/ycZdeYymFHkoptzKERNFrMJ3Y4DfxnfuWwyHliu9am/7aw+pq2O/2bPhKAjph8Oy/f07G3gQlBDrTMmWR2N8uNJlgWEsuPJelpN8wyW2nYxyLe6O29Mhz89lYZORLqljqTNPUGOODxQQ543KtGy3kD7lOjt9IFYr6m4mozbcX3io+FvHsjD6TI653GfnXor31sGt9D0liPuqDX/EhPgA1s+CNZiB7VC1PoHsnxSm7kMBikC55nJnNMtLLPGhkdHllG/yqe9nLa7MgVMHQpZ1Yg/kmfVHslQ+meqN71DIi6qxbn7fw1yzi40HipS9FdvB/jSM+hrsY1cbHEBB7atwIvEb44QFymcGdXwPI3oH8saSj03ButkStSdzXxZeeJC17t0ytWPAw3dH1UD2IvkRTMbwN58fZq4Oei2v3KsKDcHwoPZoBr7F9qsaSdInRBC0j80K4NDFfCce+ZyO2T1qFfyu30Vbm6OAyn9zPlwqg+JFIc1XMjlxgcHeQd5sgRGxv2b60p0HCf2Qjq6+L9ntVYfBBO+CLxofxI5ABJ+OBlYFCykosMcOziFUaC5pnkGH55IAMBs54HlxYekdwjXSu/5vNOV83fsHc85DAcnaCfc9XAiC26HavW4arlXfhtkA+5Z8x8Tq5OVw0iYTNf/R/lUvWBrsR83cXHArCsWtAjkUnLLqO9rofYMaVbD+TSjhGR49yIadu+NDHaXSZOrCX0Hz1/Po7OSXbUJxZ9BhSj95Auh16c44aWZq2x51zt8fVGfiibgY+CXJ/i4l8SafwdxorUyy/DFXDUcpul8zkOfmCcy66plmzPKI+vTznfePOrJQ5L591UDcpLV82dMiCCJSSh+B+ECZ3lrD83WCfuewX6Lq4xOhW5iHguCza+9gwjMe7EvPl5nNdn1G1XyKQGZ7MunOBJ+0SzERfRblDB3Wg2JD6FEeTllvnzVV+HtHAHMsO9J7pMjiCnTHbv0f0ZVN7G4Vzjncfo4UmfsGrVAISrBhHu6L46giTT7ugyxGxGmFFX7TtYV9Hlhhg+QfN36G/lG4ep6xG3IwuRulZKeEYyxf7f2CzRF1GfCE5H5738YobyVy2aLyWdlkBIXIFuV3Zwv9sju6j0nWJ9pvofyV5fpL/FnNjDHyU5sT3NGRbmUM57ksgR9xu23YRaQfok9QsyN7T5BKJZxNJ3npJjetRVkwMNNn0u9tZ44IG0io4MC1tjGk/ssxUOS5lYiWhTExfTbMynRrTepkxc80AYsuCPVX4OZz3W7xCgedBHH7SBXDtJsLNCpADnTyTRwmnF01k+5T81vyBe8xD0QkG5vL17lVmar91TpPhkbFBWCwWkHIZQioTZSldQ3HgJ4nYmLRqJJedurWdAVA0JZ5L0+IeLwaeIpJHIkj+mmcBAKDqtZRsYZCyqtc9AzUm4eTLyUykPPS0hOznNepK+xcsIvPnGjAi+dUhccXE/x1HkJ8iISIvv5meA51KFkK5hWp6eOOWT6ocilmAoMmTfDRFLZ2e2xVK9XZL5mk3ZUFcXx2d6bljuqn2SJeyNqm8TTI0NSuHb6I2CHCsuzbfJG+3l9zZky1lSH1o+aN3tepolkO7U2qiJPziNxjpFdjslno9P4t75Bu7ZjiZxz7cPuBdxlBG2rUI8qylzqTjVaPT2evp/vUWbmDtO5t1e+8hX1aDD5clmzzWa3fRhstlv3sOaXI8c0jCd8h3VfG6kV/Ad5e37I82/XjyLsFS+erDM8NMkUe2omLHMRpi9NiNyTthioPBxQuHO27OA8WutrppbsrD8qMmN3KSEH5ok3BuIXKr56r37IvmepY7IaM9SO/HT1aDkTb61zIX5ViWyo/5VuqqsNfeD4v3YEZ7eoypPq/4nPMpaV83nsLXVQ97DrtrnsLP41yM0qLJJVzbCrqVbxsTePEjY+9EfMR+qr8F7ylXDlnkpKi9nzPlHiY+qsgF1jiTrrLTKoG6cecnfAPpjFm2ymAlE10yyySLe8ZQGCefGPRlcWJNsDPOORrrRDG683cqvNGUzNoA2+J1XtiUT/EllG/TcnPlvh1oZVysb1cpmyayxXX2bruwwAxMom/geCDudc4xEXJqyocmHdUU7hJU7xtAKW0PmNmbCzW2AIfMpCQbAYBZTkyQ7AEf/5NA640wVXYOeK8HBo+xNjrJX8WiVDUZluccRF8TLXgIzcl46tCM5TT6seZrnxP8DAAD//wAALP/TrL0PfFPV2TieNGl7gUACtFAEtGoFNKhoAckCWoVb6p9ASmgCYls3RbvoXkFygU3Cn6VBrodgp+hwMoYTHHtlEydiFayFMlpHLVWrFum0vvbdTpe61VGhSuF+n+c59yYp4L7f3+fz8yPNvef/ec5znn/nOc9Nz9fU8N6Y3ObVlueq4TY13K6GO9Qw17LvmTDcoSm7IU9Tdnm17FnwHq0NZbEM1qRVbTebTMyz2+lpdzesmscyYp6u4pjnQDFrUsMH1HCtGj6shhvUcJca7lbDPWq4V6uaaDGZqMUDqS0qWZTW1a+XG5i8V5W3uOtD45lnT4A/GbKY/DGWC73yqxdLpk5XGva/hy+HjM6J4iVo5g/Cq/u0vfJGM3ZV/eZdfx/p4L96J82kyjvEwHdADnQwwBXeYa8chLMIV7OMAGatpSx75TcmSKXCVZg/kh2D2tpTmzFb3hEaxJr4Zx9aoKiSzzKCJiyYlyaqvpWoupkAVM16mVm8uOvt0ecx2xJZvNfEjmpVS8RQJokKG8TbFd9bXcmsl/fCkwmAla+JBUsBLy2Ya8bKhTmOUGa1qdtkig/CFsxGY3u8mrI3pnRFuhysbyf8x19WLKYKLBk0d7bj0JTt6470Yg/hrp07oZudXu21A/C+kx9t6tNYA98ZPqtduFz2yg1UGwBJc4Pxb4EuvRW1fx7u4Panz2qsd+HCqBaaBNA6xqU55zSY6ZUskx3TqlrEvLPFvDeKN2Oq/5cJ/AOWO6WItzNf07RIeKNpVQb8tawekZoZJITZAXNmFgT/bkjMPwVL61K2huZBeS10vUvZrFzDXsvD/vY=
*/