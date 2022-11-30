//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_IMAGE_IMAGE_SAMPLER_HPP
#define BOOST_COMPUTE_IMAGE_IMAGE_SAMPLER_HPP

#include <boost/throw_exception.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/kernel.hpp>
#include <boost/compute/detail/get_object_info.hpp>
#include <boost/compute/detail/assert_cl_success.hpp>
#include <boost/compute/exception/opencl_error.hpp>
#include <boost/compute/type_traits/type_name.hpp>

namespace boost {
namespace compute {

/// \class image_sampler
/// \brief An OpenCL image sampler object
///
/// \see image2d, image_format
class image_sampler
{
public:
    enum addressing_mode {
        none = CL_ADDRESS_NONE,
        clamp_to_edge = CL_ADDRESS_CLAMP_TO_EDGE,
        clamp = CL_ADDRESS_CLAMP,
        repeat = CL_ADDRESS_REPEAT
    };

    enum filter_mode {
        nearest = CL_FILTER_NEAREST,
        linear = CL_FILTER_LINEAR
    };

    image_sampler()
        : m_sampler(0)
    {
    }

    image_sampler(const context &context,
                  bool normalized_coords,
                  cl_addressing_mode addressing_mode,
                  cl_filter_mode filter_mode)
    {
        cl_int error = 0;

        #ifdef BOOST_COMPUTE_CL_VERSION_2_0
        std::vector<cl_sampler_properties> sampler_properties;
        sampler_properties.push_back(CL_SAMPLER_NORMALIZED_COORDS);
        sampler_properties.push_back(cl_sampler_properties(normalized_coords));
        sampler_properties.push_back(CL_SAMPLER_ADDRESSING_MODE);
        sampler_properties.push_back(cl_sampler_properties(addressing_mode));
        sampler_properties.push_back(CL_SAMPLER_FILTER_MODE);
        sampler_properties.push_back(cl_sampler_properties(filter_mode));
        sampler_properties.push_back(cl_sampler_properties(0));

        m_sampler = clCreateSamplerWithProperties(
            context, &sampler_properties[0], &error
        );
        #else
        m_sampler = clCreateSampler(
            context, normalized_coords, addressing_mode, filter_mode, &error
        );
        #endif

        if(!m_sampler){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    explicit image_sampler(cl_sampler sampler, bool retain = true)
        : m_sampler(sampler)
    {
        if(m_sampler && retain){
            clRetainSampler(m_sampler);
        }
    }

    /// Creates a new image sampler object as a copy of \p other.
    image_sampler(const image_sampler &other)
        : m_sampler(other.m_sampler)
    {
        if(m_sampler){
            clRetainSampler(m_sampler);
        }
    }

    /// Copies the image sampler object from \p other to \c *this.
    image_sampler& operator=(const image_sampler &other)
    {
        if(this != &other){
            if(m_sampler){
                clReleaseSampler(m_sampler);
            }

            m_sampler = other.m_sampler;

            if(m_sampler){
                clRetainSampler(m_sampler);
            }
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    image_sampler(image_sampler&& other) BOOST_NOEXCEPT
        : m_sampler(other.m_sampler)
    {
        other.m_sampler = 0;
    }

    image_sampler& operator=(image_sampler&& other) BOOST_NOEXCEPT
    {
        if(m_sampler){
            clReleaseSampler(m_sampler);
        }

        m_sampler = other.m_sampler;
        other.m_sampler = 0;

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the image sampler object.
    ~image_sampler()
    {
        if(m_sampler){
            BOOST_COMPUTE_ASSERT_CL_SUCCESS(
                clReleaseSampler(m_sampler)
            );
        }
    }

    /// Returns the underlying \c cl_sampler object.
    cl_sampler& get() const
    {
        return const_cast<cl_sampler &>(m_sampler);
    }

    /// Returns the context for the image sampler object.
    context get_context() const
    {
        return context(get_info<cl_context>(CL_SAMPLER_CONTEXT));
    }

    /// Returns information about the sampler.
    ///
    /// \see_opencl_ref{clGetSamplerInfo}
    template<class T>
    T get_info(cl_sampler_info info) const
    {
        return detail::get_object_info<T>(clGetSamplerInfo, m_sampler, info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<image_sampler, Enum>::type
    get_info() const;

    /// Returns \c true if the sampler is the same at \p other.
    bool operator==(const image_sampler &other) const
    {
        return m_sampler == other.m_sampler;
    }

    /// Returns \c true if the sampler is different from \p other.
    bool operator!=(const image_sampler &other) const
    {
        return m_sampler != other.m_sampler;
    }

    operator cl_sampler() const
    {
        return m_sampler;
    }

private:
    cl_sampler m_sampler;
};

/// \internal_ define get_info() specializations for image_sampler
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(image_sampler,
    ((cl_uint, CL_SAMPLER_REFERENCE_COUNT))
    ((cl_context, CL_SAMPLER_CONTEXT))
    ((cl_addressing_mode, CL_SAMPLER_ADDRESSING_MODE))
    ((cl_filter_mode, CL_SAMPLER_FILTER_MODE))
    ((bool, CL_SAMPLER_NORMALIZED_COORDS))
)

namespace detail {

// set_kernel_arg specialization for image samplers
template<>
struct set_kernel_arg<image_sampler>
{
    void operator()(kernel &kernel_, size_t index, const image_sampler &sampler)
    {
        kernel_.set_arg(index, sampler.get());
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

BOOST_COMPUTE_TYPE_NAME(boost::compute::image_sampler, sampler_t)

#endif // BOOST_COMPUTE_IMAGE_IMAGE_SAMPLER_HPP

/* image_sampler.hpp
oH75Oq/ibqo6j8ReG3K1HK6580l6aF/Y5Eto92YUGWhm7zmBrKSwUiSpKbVKLPJnBA3BFKoG3v+tvMc01MRTTkSIrTY0FJLG2izqJy+zggiyR/z0BxGCcM5oqo8290vZyb7let3yvInOFgOGMWLhWeU93XLs+dh+5Jlx7cGzrxhqJWBiYGBkjQJyHj+Ok1SU8mffqTYmvcadBQTzkIBFHuAjAGhqE6S+BQEcVQEY7cftCD98by95eDPpuH3ZGky/WdO9WU27yaWJNZMGJzHipAZY1AcEiwJNG5X5Psw6j+F914w+J/V9qRpxkmdMg6tBHXeCNqCT31BL/wet7LEN8q+CHjBCFNxrwGsZG5iltBkEm4MRQ86QfbhoTdblJyuQ5S8K//YZ1AFi22m0WtyFtnwgEQt89ANxul+IC8k6XO1pzj0W6/kHDu1qsl5PCA+Zihh1xwlBoFs+yXERrqfgl8SFjRfS8p2DgWr0hsBHivYyE32edn+rMGmVE5fXE1mJuY/ksgrTw7CuSBAC23gnBpBGmdZz80l6qnz3Vuz530lG+15WxmTQ7vITiwfMPHsDur1EbOyJ9lpSwWOkXSmZeqheqR/YQ8H+yp0ZXFgKtGdEYp8Pq23hPYoBiAywPOPmnQQqiLX+Pi9Ou9wWi2IfLsjlD4lmZXXidccuPmtde+xF8neWw4JjRJMuA3Nj+qYk04ehoWQlxMFbEHVwOtyO+mfuUYHkvpK0qv22MtY/HXEwkeE5LzU3ii1eDY1E2WBqGHrKmBfJXqsnJMM6qNq9D6+IbIdAYzQTKNQ4RJtCuIxk1G5aInPWfHIVqrMrX/g91lzi3SkbbFrdgf9cTdpIQySyY6WZcJ4luUg63oqXTPvIEK6yO+yIN/mYk5e71mjVwIRSqRUMrvXqVXoK3lvuZKTjpaaK7iVLoBbvD6QHFx2i0mHJB3ER6eYfjEtSyRWDfKWriKixir3IKJDHtbe5wuuiirk3qyXtUkGRnNAEAyhZAo9qKe9rZ6NibqauOlA/IDzB0newo3HTWUPvR4qH1XVr/D/1IAQfZut8qd5BAdyy0t2cUYok09zuko02Vf6ulLJkGPErCeyIIgsYmWA6TlysbwaZIbLu8m73hW5mVHOzFks5J0ELi9smw7C2BxvFe+VB/YXbxrRSsQj1K0IRvLnDHr4hOPhH55bigvyC50rk5oo8gXtic2SOLGKIKXKYKeVeTd0SXRvzcd3vf1O5PAndbPuP+dRyW7m/sPo5EWANAymny2hljEJKMhPz39bGsOPidVcGZbmS/14AjIXpVTf6R1GaiCINdUI5VqnJX+KoaC1XzaRBrh+3nul1lA2+6gqxXsHd8G19x57354uvYAG5CNben7bp9u735BJNV6ryadMkMqsZWDydyZRzeYvHxdYalws17/ZrisOIkglWzvPxXRz8LqdHeLhE7iSETCioj5zITfImAWFKKG97q4p6Gb5W/X2VXTorspyrFhQAE0mM9kVR/TzsIqjn9qTxMPF8RMTmM8ftalfmXNZzx3dhZ29ZDeBHRaOicXNl5VPk25p6wgGsjhbH+5bhUgPxJQihgSHyEAIGttonUzjxLofVh1FiHf/TNnYd9/0zqBmqVt3dmvuJYUmNQxRyglo9QJuvhZznFqCosy++reL7Cc5stZV0N+Nt03Q1kxE7OxOJKoZNmB+8EUCFv9BRhW8C05PFEhHBFUArlORYwEMXQcvNLtuZJZOSjcTUvkoV1BA2KE0dbkaUFfaX6t75CZfIIKFLUxXKUjWzGNlSQM76jHaq6iYd81mE11bH5SXjNRVCNI5pW4Sf2/76B4CaZZ5O2A9Cod2vZU8N41Mg2Nk9cn+VtyX+BU3Cl9f8FSOOF2/6i1s1zhqYl8MiMSaHIzW0gbQqw7WTQzpN1T0kOlDMYEboYeNK0gSu2Mz2UvIB1vKkVWcu1WE6yb977P3FgwXW0VLiyUajW6GjvxtYKtUWVDuarcC3lpTxAAIs/dPTQMaWcKxzuVO/LbhAxmxJT8BBbzjm9q9lNAqBa81QQ10SahBXBHgL8YWkpEH6+o9nSsKgk6ioLod/q1F3TtxXuf2L/iAiVk+0HTJEEBhzBExetJPpqJM9Hn5LUMtbehzQXlshptay/dP0ARda7iznkOEY0r07jXAxGtYibx2LswghWC4S6t8mZN53Wq7KsmrJvRVbQdBs2y3ApIB1Bau2+37vvfqyU4PcGQiMKEsqTy2H4w9viHl5q1Q4nzjmu4MVfWcSZabeATPQCO1WkocarNzASx8fapNN0dzDveLRq+CGJVvs81NbwqfsJx7W9x1fL5fCJN+3UNuNGo9/WC+e2bpeJ5p8HVNSih8/vCazeFoeWUvY7AI3zt8XuoulDqliSnKkG/sA0U4ictuzOymZr1/qxbV03ksC4/UoL4JN+36BxMBwGYXuXDzP09NwUMD59EiJVFUMe5uEbnZ5h1EV1/f6NrZfxMXRtoADOXbndYL2Jmb6mwF9AKcAz0CZDJ+Zh2Zp6nonwDnZFAmz00b+frmvWkGQQ3KODQLWLLVm6pOmnOB5+7frQxn6Bv0mB6Atc6YhrD0QV4EDguKkSEDYp1vPAo+VO2wProteFT9yO4HGrfOCg2Krbrvu3NLmZ+GnPE6zZljF7QN+obzrH94ZfJ+HnWf7V3WldvvQ+hkXvutCubCsjYB87OfFTm58xVzf2a8n4ETgZoNKtm7Q8NsvtNllnwmxLd1ucxK7GylP8198b6GJLjv/Ath2794hb89l8Dih5X46ptVctl2znhIgVfOPoX0L/4SI6GtFreJzSDEiRUccUYePbTTXZb09VDTyIF3Tm3rPK3VkDekmjrQ8ZpnaGXf07ekVuKPTSXcDKPFb9BWRK0KcSPibuadxwbQCHPVhAPiTz0CZieoXuOcR/Z5TJGIBUM8R7Pct3sQ9hTP2F8AB39ifP2uDntoLIJdTG5ffUy8gCNeOK3fDZUf0uX/w8l2H7yFDrregvLUTqOk43hK7C0QFWj5A48/P2a5h+d3V4Cp73t4n67XnfSl8I22d0BeUxU6prsHs3FBboTnzbf9yuffsGlS27o5IPr9vuqFvTD2VzgCiQPniS0mqIM37Z3jmp5ewPGUf/D+U734Lj2igpDqmT1xbP5r8omKCCBKi8b+mCgOD6g6f7UJcCT2UmOGGUCjs7jO0Btn1b3zIFSLC1MEoBeW5S3kt/ogc5i0xUYBhe1kTIeZvKBZyppqKD3pTrqUai9pqFORjIRLqrKnLsnhBFQFTmAC5NG3x8+mdn7ysk/jpIujKXnI0l1gbXAs8vJxuNRPPk0ZF3d2FIsupi+p708Z6DrA72Nu0rFHSof4henk7+oLr/K046ahED3UzQu0IhVnGIAHc3KjauPC3thgT+PLpjupwtpZOGhoEObPMRNaPmSVgFZZTiY5j7fR1IT6KJPZjz9hPj1X/iCwOYjMo59e3uuqxt+EGicfEjXDEJGQRmKm5hoRdG4YlGYtNgtSph+Crllk4GbnBwGUHehAL5Ab2LOVpYaKnmIHMaOn9y73X814dIaG2ovZUrBsLj6CmROFiR+7trXOJeWu+kAdGnb0+/7U9MUXFWi4iOMyuH3zC7B0CuWFGnVYJWD/DzUAtqdp6x3vf1jzSvOLlomNOXuMExzVKp2jLwtXmgOaoORXXofW4Z7B/iDUUCu1TtgCEsZEsZadzM1Yrr++54pkibL1Deq5zdtp7/calurqrzMRA8RwtbaBNxSEwx8K5s1aQdwdXtnOXi0wzLg4R1Oa7SnqNeTYtqdlOT3dqJyeHl0xs/NOQN3k8xMVQmdksGjl6TSjIf4FUkLTUp8YTUPbcJH3fkY9cF7VlUx3bkvx4BYxwlX7sqJiq8Wg1Wsxkmb6qUaPDMpuS0RfoN8II/WCLoQltzbQqiDHfCqFIuwhpErwASjyAcoqIIYqg94OJZSml/zkPJaNIyQsvuquTMH4D+cHzXl6QwSQ5Z7ne93QARtoKpFkCyt0Q2wQxqzUn1hXAsc/Mv/ZYcGEmZzB3IFVBtD4uGR87cxYK+Ue3PaYGq4aajHcaa1j/mh6qkCeiep1JXJhkt0Xxkg617ZqNtSZN3Txie6Vm8rgQMqJWEHwKhq4aHxZ9xhfQs039hTJ91i0MhGwD8ekZdU6XexRgxxX6nQ7Xkr+2i6+249AyjSEJRGTTV9GZbHWEqJ49TSjj8O+9miRAw43kQlZdI4uePnqD33OZskq9C+nSX7itFnUVysp9MkgD1Ph1ziJvPBJ5QyB9uA+LKPTGCQ1o/Ma7A0kfluKumT4zOPCLNjFf6yqqFW8t0CwD4EYMeBYMHRYdlvlk8cdF3me3DTHOTkUy2aqSQ8LxMZoNf5jhVT328EtMcTv+uwOwFzomGP15oNA488k9YZoLzpvwwdED4IUAcWNn+dV1SuAUrGbKHlGKku75ozW+Ii5t6uoVphPb5qURfuhpgQ3AQR3gKd1V4bVV/x2KsAZ9w3UuxpRxuHYtmTYnLH2Ry8Xtq695npY7XhL6+yD1VV81mkgGj6bhvqC9iJOYsc8/07BBTxrYR5HyLK7UuN/d5U5YLWE6Vh//ng6qK02VoKo2roM1FydPqvSJIldb0hntIPVnTwl19n1ZxJ+mC3D++3s1ayutUfvBzkNv3wRX4li8jUK3BHHvrJhR2/GWIbnwFuIKJJJIVa3nIc+SmgL3p/gkkX7RyD4JfWLrwzWJRPaywALZ6IHr3JbynyK77yJIeWJSmCIKAyxaeeYvJXaIDbAwGh1Tl9fu1lte8oUEADYWirBOW1fT0+uZ3wVxZnr1cqY+AikriqW7en7csPWrEmrrLpn6lv2t8f27XB01LfG9R9Jwdi6A+haYbMwsD0IIrDyeWhUbgNZDBtfAti0b1J6hi1Y/1zZy0gue1O6cJrT6VAHFv/MYpxiaC4hrLbGwc06gh5vmY6Vgd1lWCV8cdjnT1JWzrODmDQupJ0HXMLvt/kjb3N5iezi0psAPaQFufgTYGMngIX1y4vl3iwthHjWyAFkVdYanYLPB9uZiBWHTN2ZeVDuJLrg28S6XmFoUNSgRISa7SXDlwVPWZni2tcPMuA1NitcQHvK5KTQW63BKUTacLlG/yV5ZfeMUJ3cFr3fOBrElUa8Q1gMlfVIh3DsI9r+k/eSwEonyFmxufXQW0MECtnv3Ad55tvzMb2JSiWHgxpw7QZZkFpH5/fr+2mu6JY7//IeB/SgFB82r2/KOozqX4+vU8cVJHkiQrQGmH3JcKIAT5QeG2U/g01ubyZCc53QKDyAF6eonwapZKLMWHcKDvC2jSwzr4Nz/dpSkMGtqaQpeDCNtNTMrKVk48jtGN8ToYAVwyyMTt0r/IevnbJIlVgGefKwUcajI00Adrnypfga0t/wSv6uxSfMlhxjctJ6BH3yLaBxAhx8I3Ayy76lLm713pxQa6T2tzfsseE+zV/jyOSx4NxwReYb+FSlIRrL6IA8hTZB55ZkU6p1+HwXRkM+NjbdM49/i6dttf9idf5xi2bLPOM0alVGNM3WbKcgR3cd3NmFODUQgRIk5S7s95jB601skhFQ1OZj+g03ifLubEhWYCrYhHo0P9McpsYBCmQVQTyZaBQcZS6B1go8vV3uJVhpLxIn+3nWkNQ55+Oo9qMXBu7mO++t3dhtwLPYz6JM4b5N/arEtwYn1T56mrZK2fpm6W+Egf1WYYfKIYlW8jMijMGP3GC7sd47b/XNhwXBZTVFKFHusXB2qCXHQVYhiqJCfjoBatlKI2HLQS5DBLUPH2PqzTYjuvRz/0rJXFTHdOdzg3uqO78IQG8XQSR6HCGVhUeNARPYM5w/RgrSLmiSVLP90plCUU4witqGhyzllln0ZcuCuI+7Tdmjn/uknMG5shvPCL1ddy/KEepoaGfx2GVY6AKAyY4xTkQTe0QpqzWVVtwoM3gJqtanFeO3/tRlgpl9gQ7fmAQ7aZZtyVSoPBNE8cLsD9mrlozDG8ec8nFFcNJ9Vx4mhlqdbi7yGlGHWOs0DHB5OiTzQjCsZ/OkBWuptOdmoDmerUE0NKnJM2Cz0LI+TtsKx2Y4J46IuwGxLZNhHnZrgqkFQz8+tgzRC/U8PmhbM1WKbGCvIcSDy8MAG43V4eW7SFQF1uIisWTBZ8/JBR5VA8FQuAHXV6Uc3UxbA5DkgtLNiuabt2efcMmTFKg/xj5TE51O0x42zLendKdpsNx+0rc8PQteX6gWIHPtOOC9AjGlK7MTSvZhsP1jxzue5bt9m0r+N3S5AuIob9u9/r/0CCG4Wh+n3an5Itrrvt6vuA/Ew+io6uaUQQ2DFEGebSXtf8s7gt5n4d0shMan8cdT9HAFpCGbanud10vbAdjF7YnSrkCA/b8+c4fgYz1AgDCQIQ0H8cRMgAcq6+OK45dgCIBOIR18QIOW2/vglrE5dIAH9pJn8CMhI/WwdRhf/Ir9Y/fUOpFj990J3GyRAdL8sM4URlIAEpH97SOOLP4MGQAjih/GDBizF8se9o0IYWAiNSuGn3W+ABqTFQfQsUiuN/vRs0iJkuc3QIhjp1kuB+P4zdQnHLwH5TRNCMZ0/7gIaBDGIH8EfCqQczx//mQZh6L9GcndQIvybhcAdF3EAn6UrBEjtthMEyGiuqzjIz2Ml3P8mwgodzm+i4iCJ8nSI1MGXoAG6WlVoELTcmnSIUV75OoRhFP74pL8XghSh6B1IAIQAQTgPSOBCDF/cGxqEoTn/EIUMmp4FCO7xmjV2Fsv18tt/LDasMlG5H2VEeC08YsYipUWPVs+1W6vDyjHgEitFu3MTuNPyeiOrXd3F0oDsa9lNqRdccbNBir4HTmVfXvWEY89/kAugvEE+ufzv+k4cuIcrgNPmlO0c8DlOX/US0QdIB5wQ6/iW43qR8WYD5O0l3EGQc0OLwbeq2QX3PRvemDLWXPURMlVfxm/7CRMuexuPn6Z0R5z8n/AiLSAKZNaJ4khGiYKQs7h1Sae+ASjzfaXzvf8+fpqd8kaNDHtojw990P7NmK9vvQebv9n3luhvj87Z3AYILJZsbLJ52ZJAbnwwpX8MPH+IMb4GXr7CZ5giGW0QHMySyCzG8CNpOQC1tlzu2W+YdZyeRhfuXrRgd5CEZIYmb3ULXUbyqP7qeB7Wqfxl7r3/Yz++npkfeya3beLvXZE+zHt21hjoXWqC6sLYeDbiYmyCur0wVRAaQW2CynNsgvoxOUX9QmWCCk45RQ2nnKGOrTxNDRdQalkwy9zIbsTQyF6UoR5WUZI+nO/ABK3Qb2AikHi5f1/b0dcrOXp0ciV5Lw+fOHyYPtyZp1Dt0lDnoa1Jtmm7aJDqKb/CKGhSr8yClbuEk71IlbXsjMaOV3oxaJLWczKIIIBNkZVXL+kxXkQb7dzHFngp5qMpE7JoDDaOgpU2fIpLEW0QHc7wdmW9dzKAPxX8sbBdXD2Q1qvsAEF0EPPFPXfWwo1w2O2XjEWNG3ZKKkZ20tGj5TG1Av3HKY1r8VkcLcvmOzWYSbg0J7yL2+1Yx8Ubg3BfDw8lvd/x42mvvQOSDT4UlQuGAFsI0QQM3NI6WNeDENaEMlQGh2IS/8zG7yh43Dk6WtF7VzyCUGVCwGj76ykhOyW1i55G
*/