//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_TAGS_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_TAGS_HPP

#define BOOST_GIL_EXTENSION_IO_PNM_READ_ENABLED // TODO: Document, explain, review

#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost { namespace gil {

/// Defines pnm tag.
struct pnm_tag : format_tag {};

/// see http://en.wikipedia.org/wiki/Portable_Bitmap_File_Format for reference

/// Defines type for image type property.
struct pnm_image_type : property_base< uint32_t >
{
    using mono_asc_t = std::integral_constant<type, 1>;
    using gray_asc_t = std::integral_constant<type, 2>;
    using color_asc_t = std::integral_constant<type, 3>;

    using mono_bin_t = std::integral_constant<type, 4>;
    using gray_bin_t = std::integral_constant<type, 5>;
    using color_bin_t = std::integral_constant<type, 6>;
};

/// Defines type for image width property.
struct pnm_image_width : property_base< uint32_t > {};

/// Defines type for image height property.
struct pnm_image_height : property_base< uint32_t > {};

/// Defines type for image max value property.
struct pnm_image_max_value : property_base< uint32_t > {};

/// Read information for pnm images.
///
/// The structure is returned when using read_image_info.
template<>
struct image_read_info< pnm_tag >
{
    /// The image type.
    pnm_image_type::type      _type;
    /// The image width.
    pnm_image_width::type     _width;
    /// The image height.
    pnm_image_height::type    _height;
    /// The image max value.
    pnm_image_max_value::type _max_value;
};

/// Read settings for pnm images.
///
/// The structure can be used for all read_xxx functions, except read_image_info.
template<>
struct image_read_settings< pnm_tag > : public image_read_settings_base
{
    /// Default constructor
    image_read_settings< pnm_tag >()
    : image_read_settings_base()
    {}

    /// Constructor
    /// \param top_left   Top left coordinate for reading partial image.
    /// \param dim        Dimensions for reading partial image.
    image_read_settings( const point_t& top_left
                       , const point_t& dim
                       )
    : image_read_settings_base( top_left
                              , dim
                              )
    {}
};

/// Write information for pnm images.
///
/// The structure can be used for write_view() function.
template<>
struct image_write_info< pnm_tag >
{
};

} // namespace gil
} // namespace boost

#endif

/* tags.hpp
Dg95XuKT/oKeNXVoFYVhMcatRPnrKzCGxWic1IJf/y160K62MOGLo3hauBml1jGWvnQpOwx4U/+sNA56YkZ2Q3GxOHrM0+YFvELKRmdJi/wHYdTyEv9471k1eoVu9zxIBfXK49oiWFC3UvieWZ/HoOCo6l4sE+rQCr2FldmFnleKz16o2MhagMJTdk/GVwg8tqoJNMI610GRHJrVEt4walijWUsOTTNC/WnC8Pb5oYa33cjNOSeglZWtqgnX1oJcR79QPQoYQyKxXRCJeshN3dxEKUkKuYkBdNedJCc2d7sqd8UJyXZ8VQ+vmuc5SNSBQbUagZHDFF7uFn7j6zEtdvcw5u7Idbcb4W1Bjiq3KKQ8EQBygtiCtjjnPg6AXlnu4Ad7VTU6Im7SyRe9D3jj1P50Q3JiH6Eqw+Tgs4S67YSg9dK8QrO5uWfws9jft9Ckysd/scGMB+vi0wKWnSUW2Y4aWaGPhaFMjmYW+8tNdFeTaXeav1gwWkPU04O1bFMGa9mYyR/HUQ5dTCwma6tyDdLwA3xl/hkPNKp/KAvDpq9wAdUgmdmel/X4POHvd2sFA/496q2EYWByg/q16PJLsml2UF7m14yt+Jw2VfVr1AXcItPgEUXhN/uFlQIJe9GWAg3O0r5SSa40XRg9HaFL6WMoIe7iCPzO64/qpAr1vq6N1C8o5TL5yh26lAt594PAqvg0kQrRI8DUM/eJXJyU3KXKkbjYfk+TSOhO9MX9bJDQw8rc1mIfSQvsfron+9i3gk0QNg4xvAb6+B3foaYUiSfZKNC67hJhq76TStBtVCefZ6HxUZw6WHg8zjVWb9MojHGkN/fyq+kdWQH9kt7hbZZMmbyLlImfL9gWZzfHa24MdBzOiE3CFBjdXaRWHgw2+6gMGQ3+z074lJ+nbNMt1G1VyDBgnHuUMvLenlSEPAysRM+n6FkqR+uD0DacbhFFto0zymRuP8jDgZXm4MMRo+a4YRG0DN5XxfFzq3mpNaZocoApQI97/hRTo5cmX7pX/B3um5GJD0VT+YpIbEj68EnJMmKHUKGxkwpGZ5BMwRxDsjeGrcoZJ670kivweJf1PAI7E90qVp8nrz6wGQMd444NHNP1x8EI2r5Ffoi2CgY4XFH5Ro1zFG1uiejbjzL04FYNArIAWJOiQl9JPZ8A5CnGs0wfD0LYN3HRzviEMDpxspM+9vkxEvCPrtCVs0iylRt9XmHqsXoADYI0xoLz675CNke+BlNdyTafz4dMB4f9GNl3Ds4ddx2K09dJMoWrajQ7ClgszY1yB11I3Ks+QTLgxIvt8ReRJOEwQYuHU9eASo1wjmuTJEgkOKVNTIVaikW3iesxCo4mPa/fF/JwvJK2k1IpXRu3uj07RauiPZM+IOlLfu1LHa7jwCfKEQEP4/VWPq0ZCmSTE+rKV7MlsdwlvdSVD1P/LOnLRRGs3JtAQ9Blhia0ukufoBYqvdl13Fa9jxKF8O7XzyWkvHg3+X38vxvjJlJ3PAJbF7AIKylybEpyMJIzXOek9Ly67msI7QHTZZZTnSVWqUfQnqh6I0uzYMxkqzpCdDMaTghtcjBmlFKDsVR5mDBTQKOukjN4nRUpJZb42xcoE7mwaDqayIygYcLh/0SGxVb1AAV6scCeqcVIY8gkLcdsst3PGEnnKDmgN8kGw7NV3US1rcXRnxaXoScudompu9Hli2hj8tLGxeT9fxUfwBStxWT4qZnPYOC57lmoOiIEVW7kfp6KPr2AaLjrtRilzbnex29r0LRBT5Psfi+P05iReGP+NDQleng4SiAO8X99AxdXiUVahilCqMYcjvgPvSpT2WwzZsewAIHgQsMkI3AbaJNEd31s4NNx6sCnmHUT1uF7r33W3F1NElX43mJi7XXlgC48LUZFAP8Q1pbEsvf8Do6x2HgMTYHp4/LUedHXkPg7h2bfdop2RplVvobn8lR+HTZxW4EoTwtRngkcKG6NV1sBGC/ujoZBy3Nqp64BHubLNzAeAtsyUyO/0RrDm7g//qCR20f4m787S/khKIcE3uj81ofhGi3piN7MGuBaqkBCe5y4yp7fgsgLlqIXpnUYvZYGvgOg/8tMwaEoX1PIiGt0Ppd5er3qU7g51cfkPwP6+aaFxC+T8UwiZLAWv/p4FcK3cL9nvXwhDqcpOpp/uSGme+VzJxTm1fHuNxLE3xD9rCYtOruZCO9m2QXDuelbzMXgDFj8QBfDjnjhQNq/OadCiTxZi0ovTt+FScqbKHBGqL5BBa4xIRiiLBk3fIOUInw0IZAmtcFwv1+gpKgFYWBm/CrVJPY3nyc3+u83zqnwDd758zPJmQtO/x3vFPT/5ldrU6HcDkKEj7K9EHnLePlPP0NryUOl3TchF0tYZxZaaKEXkK0aQ/4WM3Kl0kIl8Ae7Nc58EmxEWovJwLYRW0osanWrZHa1yPbmeWT7Fk0PvozFmIMYBWc5qBZyfSl0jN900yZagyssZIB66Ze0zMThyzNdHdJYJ/UpTxVWwMGXyd0werEoli6g+YpEpBkw3+bNCzQd9fJlCVeBomI2AVsTjV+oCRgu8/L74OvBl7EAOOozmArzjBiMmQbz1AlV47qh9AosmU0N5p7fQIx+5Ql8TSPEE6SFOECxoZ+F+f8ZVLV/XrZRutYXCiKpBITWTz8/rYZer0FrFj+fBA9wekL7NCX4pgaMqlS8m5/+r5haGr0j4UTEDsJncyj6kK7LGBtiRH7FbX+AGGpoQz8x7WOwU1PYSRWfLSnieTzDQFKUp+8wr9wFlNMyzZ/QMRuO/dd7UHTBn8IMPFO5tEAX6eDxhk3OKDeUj+YH3jMZyEJtG4rW8JBtakLRmhcIQT7lvbPY1BlvqqUS11oP41V664UWbEqNBhqpkTm5UUqikYXfojWiFmoFMqMN0IaP+VO6oaF8du21OPhncfBuCxpyux0U0v1t5s5mYQrtXsfIAyZ6aXXdg37N9+oW4YmDcVlGBh/KxuASD6EGqHDtJ2RNwLU2t2j1L9LqmzcxC6rduzRda+ANtFeIHuSr11EAlQGt/jdD+pdE/6nQf/Qyrc7BIX22631S4ETeP+uUqrFM+BFm3y3CLpLZZUi2kqGE3FaMCGeRFx29hPdRZS56Ht2d5IW1PO6FheMZNltZm6M5Bf2dXM5r7sJUaW0ClXmnIieeRvH5GUVQgp6BNXiyDrE/BgPivSEKLNPCr9o6oIroyi3I6v2+By+cN1S0DHcAXaO4rbvQL22go9xgqgOiwaoHTBtTNmkjXvlWL8YpW90HKFZdVKYNAJB8G4zquztFhDMtkJanBSO/fLBlQOVX/RGwuUOc9v7U2zEJLqqYwu/eiuZeFwUzqYjfhMMEWFfYgFp255sAJm8H0w1Lmcda3Sqn8v1rMWWFpkp5iFQpkog7meM0yr9k+eZC6dpCaXihXLJ/240AC1eVj9y/63rkpZJdF6TshIMx8jLBJlM0dT+G2fXxdxgChbTDh8P47rEBfNiyC0eJWqt8a0KUi7q+MpTC1z6M8Pz+79MNef0s7Jx++/GxdimjbBX8UbPmNo6yF4dClDnt1ntOqj5MWkBGqmcUeY8iv6HItYr8tprVQkY+5wU9jbP0ityj+y/V4c5dU35ShLaM2wlhKL8uNgv58oEO70C4iLo7Ksr1EmhwVCSuCIXKVJRKvqbIO/mslQBP8gvN7uc2jh9tVylsPQVukreqWYX1FNkNq/O77yaZeGEidqCny1skGqhZC6im5zmefa8IXaNinzvJ/uVNFCPy7fci4G4NVWsfxzFqy9N4B45hR7N7OwWWex3tHigga5yAv8inh5nzbOdv3oMLsF1vfVuZWA/tcT90xn9+3SlVd7WQu+hA7k487QbC9DUMhbVoWiL5CuvNU10Dtm0Pky1Eu/Bb0fQymPNG49facQvuL8OgfUeYp11f3XZNXFau+pPCiAGt465DYyL3kdDcqZQAwyQQg/yaFowVzeiqTMJC8hWBFDbcnAfUy04h0Ute7rIcQ5tBi/JIi6qHVNR3YXs9QsNWoIw25NVFK5n7FUBzv9JQ2C8EWgmufInQ2AwA8y/fNRmC3IIZXkexIHl9u19C2+qXjMJa8FpkN1/SLTG9Ap9hHMPXVJ89eEuOqrpfQbGtwFCPds+h2GAVGGDZ7NU2/ulVJ2FRxOb84ecnVeesQedkNpwT2FWEOQ0A+MxiDDzzHMXXEnDJr8QiAkSKIrX8l1owJ9HtAjgS/L3/wUvGUvtXPJRtr9INGT0YUzE2fw8sCTJeRUOMCWxVLUJRLOxD0EqgtC0u73lyvXAoQ30lvJlLb4i/X7deyAE0WS20F+Q+5XTr5etqCOn28r9uFki3uv/BJYJZfQV1zr2BeSiW7S2iRiL3lBXrl1cR3rmSHq382IsDKla0YkVcDhH/AhAS4td7HtYja/E74GdUSspkBBSlvfxaYbrUwu/9bUyNLhnknDOdbaZIQ6lGSqOky6nR4unaH7J4io76ntfuHn7tq+QlWltmcojQUuYMoAAnOjf1WuCKSw9twoxGDc5NGOgAHzHsAca5qH3wbopFhVy0HkQAvXGVzTvo/630/076H8N85bUqm1+hp5fo/7fp/9fo/0b6fw/9T6kwNqOteX5oM26wV9n2ApZtq8PdPrqpCYP9+tSjy0sbgKS6Ph8A5tf/HY/o1ZfqsIsUjugmQmQRsI4TlJ2YSjaaFVq4mmc8fxYd5oZpgv9FZmfpevkfIsoUlI9kmT3fjLW7DkrpxV7ed3eqARrVYPTv58/q0cE+hZnys/DVhniQECV/0qBkiGmqdwbmTNR5aO8MQCy3i7BHiaAYVMemV+DPt8JeY2AwKB0Fe6/8WjdvMmOMr3h4kUTby7W2aM+RNehbwtZiSKwxo88Pb4nJuIhNX0DKf1dMGqF+7PWf12R5KQEELiZQJfT7be133NwEifBveQXsM9uyM77lbIvYajJP3vJafKvZlsb4hrMte+LbzrbU0e86+v1GHBDYlto4OKh/eTsui+sz6Jt5/XNnVVIb65sZrFxvkL9kG6TodawZpnkDK7SwGxSy4stjRhUnmAtL+/kDWuiuibhqeJN4HcXYo/E30KMqH9AUBlxdnTCvETrsDVsRusgxjQyzPRZ/2UyMNWR6EKMmzEPVqLM0R0pFwLIBbDh3GjKB28IYQimsWam0KKXWqB2rDMMqWjkGrtt5/1jtHPG9D9Bl/BNlPx0oaoRNsrCJZhWA+V8wHBBme8RG0TTl+R2GwcoOEVYJBTTfFiOX6d4G90glEGEOWqoRyT1JOZxffYqkOXbtrrOwf+pxx2eQXa4l15RsXlVUhL7I/JG/YJpLmAIlSwnWmRQjlf+x4TSVWxVja5xx1ELNhO5bzE4TCb7maj32C8Y0MZr4HVjQSz1MxZ5jWngbeGsymdKXlypzLMtak88bHV+ER8CePxFHGHZ8IsVLA2Z8SlkqJlgaId6UG/38QihR9r9tSBIgwN4W7cIrQYqOZk3V/dJoBB4ju0bdToEG+uXu0gb+9b06QLCiHNhdlzeHMoPOZEXrXd71cp+P3Sf52YNS9GL44o+oo0nY0TwLG8muYTd41cd3iOUeBV0ew8zONAK+4140mY1+C3ht4GeA1xr+Sw89MxlBTi0fDgCqBM4INMd/8wxmskAcqexvo//b6X8SPh5S9nfQU4T+76L/MfwtL8RERk38+hfjwQ1h3piVtd9tMUrpPn7h9cgjNpV+f7guTdYfBpijWMFOCgws3eUMWOXlzn04M9nP5uTAPhRg2JJ8kmlqBi0ziF7u88YDnKhyLBSke1zu02zcFErFA5f+SLj0fUZ0EqCkhAZdDafBqhO/OO0/994xqHc4Lq+IdE/yeBplRRaO0i6mIVuc+xBpSVXqmlXiUC+QkPaNiZjHJO65WKlFl08RWBhQincF88SUffjkOiz9wh9djo3xKHObhLQGDFTKhoYO56y7moBzsop8kDdNTjFEc9HH6bA00s8z3jyFNknpdBAW3aoZkbcYBK2DIalF1bRi7v/8lOpct0qaEVqzWEssz6+6Cs7JRsS+yUY/lOiynCTqbM6qOKmQbND9ya90hwuhl0OFKMYIy+sHFDt/NT/2FNyXTcn35Rq4LymM3wlNVplGVJCFm2tOkpOfrQoxNGoXsNZMJKcfMMMiigCnqLuRLa4m27ZD+p5iBC3v/SdJrN0LddWsKqxYkCPCqRZMoWAEh3khfqAgBy2e5sUP+Vg2EWvw5+9KpZjMT+DHWQkiL+pqIwnuyrac1NMdaHkl8cxEbS53TB7eTNcWgpgWOlW0XAwtX5ktpW9aOAle5bxi0n6aDT5cmY9hZVS3BXGAu8+29WpVVZeXLkvScQ4xJScQgktzlqaPoyCuGAyiIg5LWlAWWzX55lFpXj9/7CO85SqvEAU+vp2eE6BCxQW8HIpdvevDid5IVUqfDb6QY4x3WW7gv/vHWRUgIvgiPpOVnz6YG5KA6pMp3wdUwgdFhydMhar/Riv34ItI4SWc0h+6J8m3ZEiEIjQLCFicz+MgSLuSifTvadnKKlfBn1S+6ZcxSohNmM3d5WrQL6yIGHWbeDoSpzmhRgZyVVl9mO/+9wBXiz+kxRvpLOmSrPFXSkmXWrFKKTkh7twSzu9cDfBXsYp1iHO/GB6DjXagEO5lBbcGeQrF8TmR1+pVPCfIkBPV1P/GOY7/Jle/1ZApRkeeCP/wMd3gIpO4w0g5nIsT0RnM3WdyR/BnLsxqimgmPOjkiazgdrbwVngJ34ev8/jXy03LoguD+5E8QgsOqlYYHSsI4GBt7Qgst1P5isKbMBaRh0czWcEKtnBxIUxDTMkL/eUdmyO6FG2VPYVkDkO/d740Ao3mBUzlHSsuJi0/B/YVZeopQjum0B52O+OZxiknB1F6sCU/SvIEfms/smJ3rYQ17r1Xs8IZwzai2zLZ49CHlE34nIym8u7WzQd8oT/RWEbA2R/Di9vPkkUh/LMn5UGeXdrA8lfBWt7iE1aufi36x3X4+Xfx836++l5NJTwZrX1YB76/cD8p65dor4AzAAS1bHmp+kIHKRu+xxgQAbmumShcPGPOglVS3lCw4MYBVXPeYgVJB6cgcXA0R4iby+PnpQhDbo5k+ZZiNmF1A4WtXQV/cg/4URK1xOrq3WBla83sPmvugOt4Zab+G7Xyx3PdZ4gYW2vOawX6soU15TaIAhQNL7FUfwTIcJFZRBhGdZ8phoSf2+o31XsXqVll75H1tWYSyu7L8XHrs6dUXJPRXt9bLasww5vxDKqxTbNFpD7dZHH4s+mGMsyKx3dMP99kcQKsBH/32Tj5oXMRLz1jMJAofylSptIEIsdLtn8vgb8MtaNwIVzDYmpcTYl4P0QMBb4aB69CxFLgUyY8Ra9Q9xITcZj/Q4F2e/eIhzA91ImHNniADzMjcEoWLRRgdu2XKJjIe0ZYHSIFPk5cQ9JogFmb83kkGkhK8QeAgHcppHlAxAZKhDSP8As2kV/8SHgnFGcRvgKKos2sQAp6elRUMqINA5tAQb8tbLUlr666HzguOLh40WISclYwKY+4whzJVD57+at4HUmm4OEUsQi9AjFCQQ4MEaOGa/aKMNirnNsQl0smgE61YgqGj+oShsl/QiIpa2bjKHuzO4LD714Wtx+koAtavEz3CZG14lFcrIIpFFj9sQoKrL4U4J3R+qK0A4heR/yGHh5y93p9XClJhau1N3jYTrgDv42muXKa+HJSpPGF9w2o0eyiojKDBW9jveIIURFWpGoJRgAALP/T8g9wwqO8+0OKSX9nTKWlzzuGK/vJBox+3wN8hJRRTLYCWUdQ2SUWHraAn4AaQAlP25lMCV+JGkS3BY4CkB+M/LQ1WxicstuBPoC16HnpDS2cwi97GIO3a9GckaAAgHEgwNhRMJHyNAIM8ziAWCYphrPSK4+E3vNa8z5SLIrX3H0PCu4Cvc79GvlJ3J40X/s7Cui99F3TGsfaoz/dhRGroz+Ckky00uKL9yJrFbUiBufz8GE23CW9zlmrgMaUUk1w3nqD9/SmOGc91442hjH8PnVrq+qh7cuZhQYB92fM6v0WCh8+SpRB+TCcV0kWqVmupOwrWLDgwhhJw+jh3Y0overSU6a/8KsBlc+RtSj4D6+BlwtXxZVSsoNvGB3TjSzOliFejdrYBDSRrT4mZ/BZmD8NWfFCoIspdH5FDs/dcxqPynhvQj/n1d/Z6J10gRjqgawYZZNZ3QdPXv5iJY6N62Mzw9jyVGB4zwEfrAQ4MOQmkbUCOP7JcAFixHI0grOzQ8Ve3laFtlHcwGbQanZhXHEuxAOTgTgQVL2zLG4SViKGhwYSwX2WTEGlSPOSAgy9/xec++y3gWEzlmnXzRUYwcfu95GosKdItwGGW99jwe/mm5WRrD66OBhwGGAnA+QU3mt0d7G9xDn2owO4nRlC69PTopfyaZcms8+iUWjmvOgw2CNK/NqFUWw9XcoMpdDM3U+mG/RYLBhP0U9ijZPc8SQhDn9zQbYVPtJcMN5ssBsG5k3CW01Kh2eH/gwIxxxcON5YZkl32EML7XziBkAB7+LYDLWxNIcdjkgP/AFgcfAUeKfxuGTUTiI7/oTO2noC38PaHngEKGs5W3C3sEOCwcUzSTwurJtgc8kJlNJS/BC3O+kMcbveHaTKKsPWtbtxBIdxBG4rGvz0s7BC2hU0yyFxfHBdzjklsFWpvh0ehHsPP3QxrPKbVE0IR4RicCvpBRcInmLRVFGDdIvlht1K9QK0uz6Lp0hLxgMtWFrwnp6UpNwpy6aUT8LcluqaPhR1oPWKt0x9c4GOgr1TdZVd9yEbevc7bFUDxDsB84noGB8UEtkD66m8WQh/BV1LffCalSI+dqjai5oH5c3VlPhm9ykVUakbjYb2E/DaqhDLJZk7WN+MQ++clcIuLoIffBJX5O0chLtyiunfUqw+jlw15g5QqrF/aQr/dU5iyUIhLCzSVw4w8laSKlH+38BWlcakZT7CDj2RYtaLt7Cw4yIZvXdq9yGgRQfmEAzaqoZBk+ZqnDaimm5KALWtzUpa7fuDb6Eo2yD9kl/WrapKdaFwZLuNpYVCs3EoeSp586jbp2KmO4szhIuD7GEIvYFlMxArw9g7WKh4IiyE7XGukRAlwfJ7efu10I76FYDC1uXw1187DbX8ocJb+dmB0yo=
*/