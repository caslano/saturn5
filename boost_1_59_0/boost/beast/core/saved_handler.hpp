//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_SAVED_HANDLER_HPP
#define BOOST_BEAST_CORE_SAVED_HANDLER_HPP

#include <boost/beast/core/detail/config.hpp>

namespace boost {
namespace beast {

/** An invocable, nullary function object which holds a completion handler.

    This container can hold a type-erased instance of any completion
    handler, or it can be empty. When the container holds a value,
    the implementation maintains an instance of `net::executor_work_guard`
    for the handler's associated executor. Memory is dynamically allocated
    to store the completion handler, and the allocator may optionally
    be specified. Otherwise, the implementation uses the handler's
    associated allocator.
*/
class saved_handler
{
    class base;

    template<class, class>
    class impl;

    base* p_ = nullptr;

public:
    /// Default Constructor
    saved_handler() = default;

    /// Copy Constructor (deleted)
    saved_handler(saved_handler const&) = delete;

    /// Copy Assignment (deleted)
    saved_handler& operator=(saved_handler const&) = delete;

    /// Destructor
    BOOST_BEAST_DECL
    ~saved_handler();

    /// Move Constructor
    BOOST_BEAST_DECL
    saved_handler(saved_handler&& other) noexcept;

    /// Move Assignment
    BOOST_BEAST_DECL
    saved_handler&
    operator=(saved_handler&& other) noexcept;

    /// Returns `true` if `*this` contains a completion handler.
    bool
    has_value() const noexcept
    {
        return p_ != nullptr;
    }

    /** Store a completion handler in the container.

        Requires `this->has_value() == false`.

        @param handler The completion handler to store.
        The implementation takes ownership of the handler by performing a decay-copy.

        @param alloc The allocator to use.
    */
    template<class Handler, class Allocator>
    void
    emplace(Handler&& handler, Allocator const& alloc);

    /** Store a completion handler in the container.

        Requires `this->has_value() == false`. The
        implementation will use the handler's associated
        allocator to obtian storage.

        @param handler The completion handler to store.
        The implementation takes ownership of the handler by performing a decay-copy.
    */
    template<class Handler>
    void
    emplace(Handler&& handler);

    /** Discard the saved handler, if one exists.

        If `*this` contains an object, it is destroyed.

        @returns `true` if an object was destroyed.
    */
    BOOST_BEAST_DECL
    bool
    reset() noexcept;

    /** Unconditionally invoke the stored completion handler.

        Requires `this->has_value() == true`. Any dynamic memory
        used is deallocated before the stored completion handler
        is invoked. The executor work guard is also reset before
        the invocation.
    */
    BOOST_BEAST_DECL
    void
    invoke();

    /** Conditionally invoke the stored completion handler.

        Invokes the stored completion handler if
        `this->has_value() == true`, otherwise does nothing. Any
        dynamic memory used is deallocated before the stored completion
        handler is invoked. The executor work guard is also reset before
        the invocation.

        @return `true` if the invocation took place.
    */
    BOOST_BEAST_DECL
    bool
    maybe_invoke();
};

} // beast
} // boost

#include <boost/beast/core/impl/saved_handler.hpp>
#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/impl/saved_handler.ipp>
#endif

#endif

/* saved_handler.hpp
Nes6dsBnsQQM4L3ttixwybg87+QzFSDujK0W6sb+PRxoOroEyLTbDR4aQUSQBYZU8Z7rEOAlpET0iCh2wCiSj2xh1HNLn6wLk564X1eGpLSTLdLpy1hrKNKmO5envo6d+Mx8TXZfsVuYSpa8Uu0XenzMlM2Xl1lIdhe1BTgmg1Vqwz38ldMe1r9q1F9df9/aZU/DwuDCwoKrSg+b5mNJygrLURm4muw1J6Pjmu0dGtwaS+fgaP+NrZ9WY6z1m4p8211jYoKDe+XL3EFTZW31czZ9ilt5pWg4wDf6Ndu7qdvDa2j8BeHiYGMC04JiIMMCo2JsfUUZvczDCzzsUVKNcWO2TPL5eOLTv+PTH6z8pMOLz8q53Q0Iuu39KUtJi8m61LNdG39be1/z+EXT5/AIcBtMzCiBenojWMO3itghpoUK2lmTDwhE2zJjGwgbDQULEnhBEMIiRH/sspAWoj7F97W/CzN1XeLT6IU3X/+BXx7xLWGvFa8jhD309fHtuOy47N7wp6bhmhqvmOH4+kxCqqSkjdLAewgZbHgNmwSoQOgiWqnNC7QGK3CGXmtgVzq8C7IBeK9VJPWKGbwUql3EgHS/GAznbQtRX92+vl6HsNk/EQqvDpk2pn3VUEh02luMJgPylKtVXTztOZ8m46vY5/vEW0pMa6jhN9NZneQiYABIFioer0e/XFXOgHvrHV/psePC4wAEmvKP62uFT49pfHBmsbikqLO7FwE0jKPbUWU9nOHOtIIcTJ8x3Jm5mcxRuKnG0xTGsxhmyvRLNz8Lv9LJvkuqU4xqgnd8Zs4CJuXyZTN6w/aF76WNaK8gnUvSHCqvsnbd601fWmaOx8ymrvsoyM+2GNpJ4dQdkVcQMiKSnL09Yi3riwtACIvIK0KoyE5oX7VTEC5FbB4wwZ39L9oimF8/HlpZD39HVcYUqi01eCDtLBFdsOfmMNo7cKMv+bDtuAn9yrs++ulW86K2tsaAm8PQ3ZLuhtptWMPUqtwuzsG8VmF+YUVDfIOP11Da4XRlQ8TD07jfsPCKnaOQBMugXfreDxBdykOJD9q515KgZW51OX5Z4iM3jjMW90C1HXj93fgMIScnuhm1hTumHu3UbUPMrmP54GUDohv7+D1JvFwYD+n87hgMSQyyiRnJW9th44BqHBUJJjSG+LElrYbQw7QGIb2R5oa9+W2YKV/W6Oa5Z89L7R82gSdJDVYa14QzJMg05Jx3hyAH2UeTPBjTO1FX8krg3dcm0anobcs0zwwIyK/jaTU5WOM/+anR1vYWAhPbqUF5vOX0AF6n+7lI+U84TAUKpsRKZuf0RkhVl1r2VhENFA1GKud25/b7tqILfOh89SxPrXI1yKdySYPx0AXkkvr4cWSao6j+qIDOivyY/Im2/rN+80qjTSEtikhsYxT2esnzMgL8bUni6rQDuPkU4v0BvDHm/4iUsdcPj2RSr7yLlXOXbARSmF8ak3cIAhVHjKuIcFLN4cYW7Kq78BqkxkWGtL49c4HzpIwkkjzUbsfx1iA8xGB2dFI6cHD9yfPt4G2UTY51pH/VogG2IwpjSWFpHbz9iE6+Y7ZKoSIm67hlxzv2+ZsVVOeFHDvTvtQX3JM+ovYmGXD9qfX16V8aBZ8TvgK0UrWwu99+DE8/vPKAYGfvZw0agvF38mxRFRJXJOCsvSxmOdF3jPyryOSjMEc1ckvE/h2HLomTde9abJROBenlXw6KyfMglufGfyDq7CDK7CSq7CQq+64O+BOyySmqUy7QQR8GhH8gqvqq9fsPHJUZtzkX69GPOGKPAMM+H3vGVZO05C5RcGxYBRi3SRMnmB854Y8Acz6TlH7VxgCKyOUS81O+AIZ8SPL7wtF4cLd53HE8JdIdJNINpdCNpNxiiRLToCiv6VsGs5OGZtay/2cIpfIDFizO6eQQWX70Bg6pWend+bo5yKYQWRE8bAAopbuuMyA1FWYe6+j5/WrmeEA0VVH+0ENPv8S4cynIA82y5yWHwaz8rg3ZmNh6e80P6fhUSGj5REjjAPleBD9+lB4vwCkWLdyCglkZOAJKa7G59caOT2yOipOMfM6p2FbgkWCnXjeRWDPRKJ3GGjH3gi3moyGSoZ9OHZVFXZVEPZlFfZlBnTWYzS+YFi+Upi+dVi+QtpeGzZCCiRDhoIAPIZIGkEL9mYBZlIspxKmomDKglxL4crrXsiSeGtRTKN5oyN9I2OHNgMPhe32frRMF34wAaRav3oFRWEkxa4aixrFvIPpeTxzcr6JUL9ioufuV71+dMOxgtC79hRP1QbiDUZyqk0lnkeEDnTlIPojT8UEobMuUNUQTsi6wJSfV78x+XZtNHaH8BUt4DGtoovivelNOo+1Lo81bYwA37wvJjSZu/xpouaCbjWLLiK4xRXGI7cZYT9L+Cw4Ljl2q2PG/dLxPa7OF5KIunee6LNPHnCb78N4zPbDZkyTTw+4rVl90ZN6EB5jAXBmbQtlWS/s7k4CszL7qa8gniGYuMc3LwG1+IpRhL0260MM8IigydtUU+3i4e+fUk7NlDld4D3HPjKzO4SsNSkhzRfeWVhFPwbEKG5Bz4NeZCwr3IOnasVQUtn862v2j8P+xnWLVGQ/6oO7HmVlY8GQjshzoZFjx9zBIM9cFuMKpOj5Rk4j2QCSdNS6LLzdU2RhM3IlpS3dcW46r8n0yl2V3yKyIKIFfdoG7tymrHroC3+Ceu4WqflyhSEZPqhEgElGM/pAMmwuHIe5T4S/DHghN3KXgqOgZdmmXJPB1s+Jp1MVoMJR/3d/ux7b8bi3LbZnvKhK3lYGkPFlG8RhCuRt+ErZfLA2btEFFncPgdXnK40Wve+STYP3wlpDcxaAl/nehiFkOkFaSRdRBfWCZ8avtrXPsHLiUFv/p4ahmXE9AfUZVX8rVjJ+ak0FmXqQo9ykFZjpgeK+1Ehb75BJG9ODwwx0QQp5uVBo75iLxoxlEciI40dGJPDn4cDG0KhYllruwlX9L22piewWzIa5RNWoTZCrYK5+dajsEr5t1EgjNqByJfD56NdaEgkbLK3uN6ZGUDUOecHWjR8Aj/r6fJd14c5m9ydfOJ+UmZvPDudnZZe8X6v1tzijSieYm8En/efUd2c7R0UF1B/Ar/T7xk4py1wXW7CHgWWdYq4R2o9JrPBBcMKcXGQaBh8Fd3/K9XvKYlJ2viDpJPOKL3ObhWlWZH5ofTSACW8WQw4AEZarJbPS7BnDIP+z/zT/BOtG6wPrIGiSVpKZZ5VwWAYxqZ6ydLPA7x7/sOuj65DrMehGy8N99SK+UZtVM00nTV9NL01rTUlMw/jY+y6Q4oVRCtuJ8bqePxjL2xwhlUYq2636x53P2CsGkTHfcllAhhJA3nrwsT750KkGAqEErfIO0B9MshvjETxA2n1Hpb5ML0SikQKezU2APlhtXAbxjbWaFsXTbkxwLl3EsvffEWqcAepTnCwTnjuP8PNeqPDAqRmYFfJ+A3qgY+/O4fl9/+C3brxOaorOduCojdEK7NoYUgLEcPs66lPOQ+YZJwpHsRofgEPGlLCZn8yzswctKITmmXLzD5qtgQwWLxp7QchMrvYfTQobrge/3OoT4kRM5dPBDA1mrCHxnSH3Idee3eRThUqIRhSdpcTthJCl1D+EMJXUbYSlhdTPhPnX1gF/uC72qOEb8dtHU/aJp0sSbPk8W5PgpLmb43iN/Rjjh00DtJv1zvRwKLv280OIJWWPFAi0nCv6iL8Q3NAAHLPjTIC70GooE93QQSyLRO3UsaDK7aXcJKiZAehQASnp9/FH2pXOGOe5D+HJrgQLhPEv4mXwFwOJ4bzm+KntjPRCYkflQKRNtuT4jO5HQkHcKxXzZY1+IQx5z41Eyw4tXUaSVc0ZLUiLo06ViHYMDUbwxsPaFpp++z+NYajjidw6mHa+OH0nYnQdJMqTDcFAOLusK/wb3rI81iGEn0mbi1SPp2MPhKR9FqnVe2wkNn/eObWPxZzfRbMCUC8SowJK7xCDgsEvIYMD8GwoWXmo+DxFobAcVJ6jiuLjhndZj6IT+HL7cgYiu0gn9N+sxa8lxWyGtVGQQk41aaNAjqFRsUJS51FDQZKRO7bmPoVRo0KX0ZPTniReu55TMlMyERgPuLMhXN44ex7+gsETBe7Pn0yGH6q6zMoTSKP66PodsgGyAzOTrpmsmqaUgNgbYnHRzNJe1nD5iO1ZsKZdkHAZNW1bMvXo83NoF8PQYMiIJvLhmSVov2Q3Zg3pwFRxccAOF4AowAY2hijBt/pzUEH6NqbEw4pqj8wmkJJFGqWCyJZatkZdrRxAjYo15FjAqXMtVOLnxKRZz2RP5QJJ3hRsTdcnvslJqKUvlBA+e1KdEE57GJ8Y0q2JSKUlE8R5JpQAT3/szc5D53nyu/nr1YkXhBBJvU3P0LJjIjRROUe4V+NRG2IIY/o3ARRQSU3UvNTy6YYchHc1Sf8XZlZggvv0xamO6hDnm9aDMNrkX4fXzzSnJu8xB2v1BWtgSiin7lKeFMGIa1ryyIRUl9K0hj/OO8KHltXwBhVX7Fw7u90V454IhljUgvFJWwXMtdLXm9MUEHaPumnUDIG54c7V2AIc7BbxbY6YEPrP8w4G4o7ixlIGglSY4/yYyV6cjaOE3+burBZ7dr6KTwFfdvfVerg9rstfE5zQG/3kjMWLPHj14+ReJpPAfLlYb4QX/Go9NsiDJ6O+zLJsvmx6bA5sCm28oBrQz4PwQjxmfB5+p77bP8pUr3DOvIqgIqAmoqKg6tGC0f2jNaN1o1WgI38qO/JTNbC6EoaXbV4Jwz8jU1QTkr9C0RdCW/CVMcNEgXIzHH2ZMUt1IyZkZx8BVn2vuaUMZMpyu7NwR6E/9s6g5V0R5pL7sMU4pdhjrXKaSXMaSXBtwnGtwnBuL1BZUzLnF6pj01GxWohypFrWVm6xogDhFNGn2otTQkBaZJUdY6cubOEiMqvYTC7tVKtmN8qMg369dya+WKGE/bk3VRUJPW4JNVxFB/VuiTcj3XiyL1Ck72T4NBwJMK1MZ1/jxR+2ZvOvZPIpuherX5ov/jhS073VpvJDd2De0OcGnfmxPkB2FM3GtQs8chSPdWP3HXIKVtUM63YQ/1CepMY/AKXagPw1Qwqa28OXbMV4WxZmCe4kW0jzFxkZNsrtxxcSFxYhVpIL4H1XKj0iwGbmC+J9Vyn3BiFt3TMHNxYhb903D914rezEED3ow7ULfvnWfWYTkM3E2iSu3LxLZR2yadhcS1kZrOrZgkbhGayywycC/CCsGuDP28QgqKDUo7OvQFug0KNv3H2yUbRM5POsU06C2NkPcrVOpMVfEGRvs0hqtD0mfdqhG2yE89MLGOwt4hPTArk2i6jgEuVHIXDxRHZDg2qQCL4kzZJZdJjPk7LikfCnM/LLrbqRxZLNCzWF5ffPYfbo0NI0e+qaHJ4bHh1n6GdbdQnfywUA0tdf1wLXHtM+0y7WXJBWrKsxWSwY1vWtQDyzYaw8Hsbeo0AlnqEVPPYe8IhjKmkVPICaHJ4txtryEopQSR/MYHl/J5oQs2PM7hh5wGXTBwgEt3cptNxe3B7YbKNlurR5GXupY27zHdumrRm+GNWM00ilQ/nt+K6jSiwT9R08m69uE59DQlVe+I3gJfslByq9zwsqsV41Tu6N4BW7FTkDvUzDdKl5B8ylpjUaR0FPXSUcPFnXxozQwpnjIannsy8G3Qpwwu3SPmhMIQnZDlA12JFhMQYAiEv/rDLIUK+eAVEa8RelZQCBa07NVKHEH3ThR4kS4ImC+KAnQ0Dl2O4g0ASskDSAV7WelectUYHd2StkZTpvb/ahj5FUya2bp3KbgBtnZgDUDXCgV9l0EMerUtMoMWGXTQpVKJnmDLFh4XeBerfs4YrTtlSJHOBe2khFnxddlshxwgLIKGBqs12UUjfBVP7OpJ1jKAx+PVm1xFUWEvKhfrTdnhyRLh+1mRO8tIq9nFN7SJtTS4zbwqXVg+ABoU3wJP49WIyPe3OWTZ/4ZF1vzXMoWPZlYe3xQMNGvjRziNrdLYBI2fvPPd+ZBN7U7JH2j6EnQ4adpd/IWporL4WHqM4rxhAhK1tR+teeJqbq5S5CGPUdGm8TisxHpmer3bbxDqB3Wr5d/5mJ4xw0hzmwGlOryzmGvXcMzouShHf9V7b3n+Ek6douBL6CO00vgkBTbQbcpZz3HBmsEy3emp0qoKqpKKZiNw0sFjUNMB0pOT9FvCkq13SpNuVYF8/LbFr15RtaFTct+tem0TkmVzkI5d8+OM9dqpZ7WYeLfkRjHijZ50VgzZUMD4DBSieYV6g0bbBz05snMQ8oYeVIKO5WVDKkpgY/MfyqwbfNXu6Y8PsfrLuj3pWt2k5rOz2vPUb2Jjhval1qbuk02h84t61nZ5UBV01rpy9RbLG73uAkQexC02xkvIFL9aH10ibx8mbxyer++Al5OXXmy7KXQu7B8vgqmy0IRkpj5FUGvrQiy2t2Y+l5LsNCb/Ge8fEijzFTVKlfJr0nuodKsoXROcPsv7+Mlwo3YyOxqM3Tt7SRUwM4JWJlksOglkqNyu+hwkmXKTYt70k3Ist7wu5fiZC2eMr5j0o8T0JlWcLlKzjdy6gSRehLr6Xa5i78caKYoXANxOmcKwuvK0itDSdN5fGpXM3OKza9AeqiXqmcGLB7py08+M+iN1VAy3+ZirZEDSCorCnwzZLq/Y21QuF9QKD9sGkp69Czd/32V1q/2N9u8LTZ+oETkdmA/Un2fAo/1peqmUh+dQ+yhm0wEpqI5n1v8Xq4GqUdkkrNyLdFWUCfIuIPwMhbyt7ywCd3bhqfFyKz6V6GVdCUmdRntbBaVlaYJ+bvBRYOenCzZJDqV0A8jQSlTXeTx/gLwlz2b5j3yDk0KQHlSTZaSwXXc/jQoFD2uXRaOSWyvH0PdNigEkZGTDb86n1PxdNxa6MycVM4ir7WpZxPwm0Qd0Zg1DhYK9T/a5rhnuF8bM3WVGT0rdxg9D1XQPj4h1L9ZGjs+nLWJd+XPG3QvHf0rnxcA8nrTP/I4edQA0+6xIV7u93NdGzOvY2I+bnZt26RxoiLfsmey7anpBz3M3su+yD6rXtNw3GZmc3l20rMIo9/H9uuvCgf1OJWW5paY0qaJ72zNaGW1RuoAJ6GfpelOui1ECJc1Hcg9sFxewv1poCQpCdQiJCTYKwBodTiRYtW0sYvsM32F3IV83Py+B5g5ZWB1ewjLbJuVkGkS5u0DaLnBjIjoKBsMZbvuIw5ImNOBBAjAHVhdDNBRU/toTWbJUCqPtCWUwBtjZb+0WUCo0sn7QH/GOze/17TGtIsEiMx1D9hHY03CVUBsXEcwVrP03Mh0H5KCvHUG28gcGt4v0vkvtliWI859Z19fKjsMW6giJj8MTSxWmq9kkzjEgNClo0f4doB8Wt9dBcJko0ovuiSZPIRD2liciLNr7JkvndwaEUv0yXVZ+7+3hZ1e4FE9mMefDLSEFUDceTRjAkvF/rj4XylQs8w7BGfQFmdQSpPTPBr+Gqvcl2gYkxrHFutAK2W8jbA1s+Mm71mN3SBatuTa9ovCoqA0qzExxl9w3L0YrKfOK6oMgLXlMF+dxGZ2W01Qa583pfO+
*/