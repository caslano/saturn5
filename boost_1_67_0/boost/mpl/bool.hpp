
#ifndef BOOST_MPL_BOOL_HPP_INCLUDED
#define BOOST_MPL_BOOL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/bool_fwd.hpp>
#include <boost/mpl/integral_c_tag.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

template< bool C_ > struct bool_
{
    BOOST_STATIC_CONSTANT(bool, value = C_);
    typedef integral_c_tag tag;
    typedef bool_ type;
    typedef bool value_type;
    BOOST_CONSTEXPR operator bool() const { return this->value; }
};

#if !defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION)
template< bool C_ >
bool const bool_<C_>::value;
#endif

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#endif // BOOST_MPL_BOOL_HPP_INCLUDED

/* bool.hpp
iAecKNG9+tw+z0JLLW/0SJGxuE1fCbGBjcSmV8UXcuSeoOFPCV0jXMgRtfu1uRHHe9KGdW6sal+N0DTefFRF4usKu/GJwrHQX3BKw2JzijgqBSUPHRwdtovY4Z78fMN4QiN1UUjKnnDtkXRL8M0fV1hL6vvpFkq+/8KRyU7j/bD6U65+S/dfaohLD9nViwk+jhFyQRmcYm6bY0jGngoSdM5R+fqkHyTUs5/MGH2qZM/UbczxrGqCL9Z+EaAF9+eljRE6aeteKF3yeFY1RkihDLvk/ri1bD08nvGcvz3MBQh8TT5Cy2KVKm34vysmih2o9xXp9C9h0ukAhzmtQnEmOINVsLakwlVmL5MtkdHAWgQYwiragylLcWccUcNBAWY8gNH8lInIfPxPQwub4wFXX0hVIcZOu1KzfpPrhxijrS+5XlTMBFsvERiTe9LjwEI33zwlPQTYd79z544k8+rUugqrm4YysNp5tbXD4Y8fF2Hwb7Yb7jG4V1x10OTUJSxxdBmsVn5FfPL3g+CIXCLbxhoKKraN1puYTlG/5tXronn3Hx6Jo54+6p0dl2Jbw9PoeioIlxV7MC/S3qwm6AUlnnujLd4dFhGI/EK7to2+0XUe1qVRfaSh88Mb6CW92c91XZDpkzApTiVWL4zbrvEoVI4/l6njoBqEc9sG+VzOto7qeLyNfsz1rcgyT+653L8/o/O3loK30O4awgNvmsA5QcKDGVhOWxsuqbHI3J9f672CZINAizO/FkAfPwhJXWB+ePgGask67twOUbNuwgkmnlOoBFH0uH3nZF3nnTlGn75cZuDU1SpRtaynz+c8zyuMRXjZZWV/G34zieN0+pZ0hXRe0vMctzovJFsRqTtg/dxY3qFwmIPaHRrRZGuQQIQM2eGkn5d7oofYAj/lZcoaDgboX9sQOwk7qtqIC7svOKNyxIZPMVfC8HLuhb3b5NP1GUmd2q4z/qdaU4Lag4x3T3iGM8yeIzFqm5WnURcF0+vrSiYCy2cqFiCE8MHXIYXOyyXJN+7+aVpgm5Aq64I+e6yAcT+IOytC/Ukv4vl1uKfSGxYy1ypaYDzhUCmht4HcS+7M+cn00P1cjCm+VwXkOgKF1vhq+wmy2hJjED9Fxo7yvZy2cpWgG0QzXhWPKewzzRESdLLNVlYXfUKdbDGZNvnfb1bEnt8jCTK56IxYerhQyiTBwgmrwABcqcL89N8ZDA7fNKFY1kf+/RmrCNg/heDCxDHC2/nET7eNh+5v2GfNRaxS4CXqxKTqIwH8nQ35Uj0C+7zlrIl/w6WSaw5GRqsoATOZ0tsh8FoareTmBP3nGN4P1d+3Q1QiPjokicLhG/lE6lB3I7CwJklFf90ZX13Aw1EjuUTwQU7UYcOhajASFcBVANOQhuUR22vokI1QF+Qq+K9nl9uZJCvjGOy6b3YlJg4tquL17+mpyIAaaK/+npYPz/6GzTY6KNYvN+ZI2v4CmOI17cN7L+zU2akAJWWYgj518GOXBKwLsX/q2F05SZhl0u8fLlLcD+P+1Mia8lYde/+m1ESg6Ziq1wKIc6nEeM4KzZ55GfrEGWpoXSwi7gMpd3HnTmm66YPuWwDxR1t7Mt5+HAQf3Pqen0yGSLlCKzvENXA8XoFjy6B21DRdEipUWqvmhV7/eWj9bdqtQHyacI5JcPMqGr455//62C4xZ2fU/61EiVDaDIXN6vJGx9FfPA1XUTkSB+6kbk6Sognx+nFNtPVoc60VSAuJuy6K3BAdCoYElosTtIZK+06PaCP7uXfcVcF97LqDq2zegj8qM8MoKeRLHzTaSWyC37TizfDoXokPrRE2TgS0nfBMK7gVa4KtMdyQTgl5bSU11AveAq9vnPPr9zxqjyD97Gs9NyQIPScXrDbH9rWoXEz4iWxz8oXpzuzvkksTEqupogVsz5yxGECH0KOjK7fDcFuhW3TZciYT8GmZCMLHvDHMs3sUIoNZL7ZOmd8N66dHM+Dt4WI99BPxjF7/z2R6tx3wXBfffYgtiF5ghP9kbj1ACPTZ0Eb3CAvF9QoNWLEtgnHp/v1p40H7NhLt/qEr1eLgJD1ssK0B28800q23Wo6S3W9nant8e8xHr2keSJmNbjQzNpMMKdjOhvacnDI9SU4qeKLGf73xLLlMtlrPNuVUIEjXuvj0OGrSW6aBZjPZEEaJrrTHUIpp7pSg5+Ejf0aZfwkE1GmdCuBOKR2gsPL+9u79YKSPD+Vffn6+y8FxJk2NEEoprIne1YL6wfYa0ulGCbOt3NlafiCyV/Kmjw2axtG814we9o1rG1GZ8VCBdIq6zA1RHx71zUycsa3hbQxICkQOMYNidRXFvPopb5YbQTfhXF4/3JX+HH/9ZqPupbaDtHcXxDsZG33I99tUyOFVgbjKNlpAitM6rnrTXCrZMrFHSEB1a2kB7G6S9jiiw2cBLDhSkFGgaj7M9k/lytytEf1tdGL9hyZe0aCsbsj3vNcFTSnu4A/1du3cyEOF7+dgldcQeFq+0KW6HybRcq9kpb88U7qm1APHHQpCPVNSNJFt3I+APpelVokXPt/UZah1G0V+ghvfNgrMW7B9ZOuA38FGjmqLr2U6smgm0yWO3x7+8myTd4zmU3KEHriJKA7VW2ycnYNfC7PDxXRM45Dzueh/gkevjEB0L0L3LEs5tRX7+WNNwqI6NPS0fRQfZGmlo/E741FWwIwE4wXb1yu4MAirhN5lZ7lDjHWbi9wgyqgu34o8u6XNLu1rK6L1r8jwgIwd7hRYqM5LA7HaOf2QYz0KB0b9YgIOiV33v8eqX/Xq0e/fCzMCSBgNIvDtqstB2L7p6TDy74ULgosJECID1m2rG+aCBSL6w98xmHRNIJqRShttuF2JHU5lXOx1hdYr/whfat3E9sHUJvjpAjTGef2sDEb74cVfYTpkQeroQT52xCOSYd6aSlsj0d5PYl+PEbpJxZPArYgIb5TYt6W9PI3fwom9zMsKQ0WB+avNkj3vtE1uNQAfLQP4rzdIKGSPGzegYmXvriu9I8wydppIt7BNT3MrHAAELPvTZoJ3uUJaN1Xe0yt3s1+H1I5BV1dXD781YnXnPao3EPsHD7XzmptDOYOQqlUMD2Di2SwZC9jpYrD6MCHRxgiuqy/U65nOQf7LdEgjVyz0WbBAayZE5BGsMieOj1rDUxmlM3PnCDk3qlLHx4ua0xB7HhYblKyNcwaftDk119x57vw7aNHBpasd+R8XwL9TwnxPB+G8bbQbRNjBsib89Wy/fsianmy8pZ2n/EfkvelSSZKqwfPDM0MXLfPOPpXLfKsx8gZikgL59tEDGXIqBHfRpm/8pTsJFGSdCuV/dgE2Fp9b8Lw+PCgrEOnxWfXgVpyK8xWhksof4lANnMl7UQ0Q++J8YWpaDTRh+HlnoA77KLjoVN4qsy4z+/II+fxGab1sVda0++CnuRdaFSHnX9T5kC4o5NUmjnwPW+Cgx0qKtB9+CBN6Pm60P2831yk/96pwiFM/k/a796yuisMkVz1vkQYII3D0wwCRcwW+WdU9jWNc7WN/dfGA/TFH6xJbr0lracoam7fBm5vPZwZViFxAcUtNyFMZ7vk9BK/dN2uKs4Cb9Jn3j+83lfA085yOuz5R0O8ff4yX1/4k7Z5M6+UrasJaMqWq8e8zn0fr9VwRIl3jCoVcNeFg8hJyiQHfGyJfrJ+Dwpo0RrF4Ij2bGABXUqvU193UOyuWzhuwWa9WWcfbrruVSQkONsoRdUh6HfKq3Xc3LGL1iA20SanswifeILWj5BKw7KDSVmhwyN2+w7UMDSwmvid8+01O6rsx4wZEUBez73BSod7j93yr+WNg2DJtbJ6SSCP1G6EqEW2HT6ZR15mJwOcbD1N7mHobxDFM3yHZ+fxP5SrCtQbMGPDgFAnoEZgj4Ul1Dvvv2avQp41qXByxpzECnKY/wjm57ByBoh6m5wdGKiMqm4HJUpxX/OmhOreIBueGQybbw7N8VTqZ1oLGuHJEnAaBgfL/pEjUsHAmVqlHbY3fct3qvE0AAuvwW+QubaRp6lygNjMz4MTWpR5Cq1xvwLEaijSQBS16S5gltRjA87qDkMwyXM4/tsnhpy+hXaNcWymrW4n3A/+YvexfOreNPulbl1pQbP66OFiO49/dtn/hHEkTrkrPpNpiPydo54koFB1TlyPOhHvCcw3eL4DNN/3M3kDNnBqbXmnPsLGFuSmIG3JvdvhzntXSwNX8PgozTRyag2jgDvcELt0eegMdejToJ4Cx0byuvbsAPrH3k1vxVwta/9J+xVkq16lxoevXzv/f9esPTT5YZHbSX8gvOb4I/u1rsbtz72aCkcHlM4LtFyK5Ip9VR3H97qSGiXXUX7jFf92Un2fcWWD8OjWM74J4JBrt/iHX947rp3s+qu8nPh/gAQ3ydtiZv+a2wyr+yc3mgKbCNfFPP+l0HbwGWUPAF/1lXUZi2Be95os+Y5wwHDRXXhQu2JERoqyGv305+FF1d9b4V+2Z8NcwHeQIaE8Gmv5i9IDhso6Xmg6AKkZYddH3p8XldLa9FDsdenc1lSeEf3qSOD8Kvyy5TQlvzHKyOPqQ71brANQKojgyF1P1HentjnCBvvsWBJ4CX6Zq7bI9tpup4S+mQY01Ro4nfXQLmUrW+CpqRjy5ssa+ExaL/YOXutcCHg94omlBAata5K3r7RkwEtjWRdtkwvARZz7d/Sq6R8N7zCFanzyobfZkTChomRnbq1eco9n7bVLW3e5ebbWrBxJNKaWqzAuHGY+BIYHGm0n9zNvPE4GW4z6twLgPabQeeHZJ1Eev02wK8c/th87DYsnaprIpwe80tzKLXnLd6mRd5iFGqaGiCvXl/jzwOOa93Yeij323mGuTFqRR5X/nSXWrJNfVd5b0NRK2vAbI5KP/PjngpwoWLWNMcM0NZArGfLJ5hI0mJd+443Lpi4qjadAVDucyhtFdg3zxC8c0DCR4WvbTLtJhIYciApjmYuqRIAE8r9M0YazOnPr8XfK+NgM/MDAQcOqAyTUquwmqLXZ49Gi2orOjI76bRn5Mdpg//CyokFHztuVVOyQhwMI+TTu9IflPQpv65o+KIcpCiDwSFjteFoImkh0ooXzdTdNF0OZoiVaP2XTg3CJY+sdrLxlfpXttH2aeLdx7TAJ0lFfA41W/3/Bhs+EzkdqlXMdIsitgcv5CobmUTvWxxc7pYmjZVb/4QJzm0KdyPduD4GC07AuX+oL9SOFMlamBzMVX1OzE5a7xhH7ZrMGcOvapfeuB+zvg4NeTK+CNHRDs+AflxTkQXKh8Mmn2i2h92HOo/jLISsFBUH/N/1HCIdaaHO2lASsxFcEJ86mdgG4OiiJHGPuDkC7AvwWaV23gXC47sACEGqfMMdqmBf8IFigrOKFKekIV/grGN7Qqvn+4dFXhL1/Hwf3fvsbqp/njQ9Z/7EToCD3fksRfU/orWEo9pUiE6N8N97iL5BJ1GBqEKYawyTz9dyaIYSOy/mzyeG3u3ZEh7Dc1xbAbu3PYXGmH53ZFochV3y3weLIxJcLtsNtGy6RC40eNvrcdXmXbjrp5v7fi71rYbCtp0fpLKxnb32XHPEPHLmDbBPk46B+JKG58h2ivBYXhFGwJaI2JxXh5o+4NM7ip+HQ/7Ob0pxiazgOm2ui4wgo/1bo7XL8K83TUu6Lv1dYIsaHiXC1wIodx4oEk1VqAfoFhfnO51PC6x8Nz45gSN4D6M/DbQmehhlpuLUrkTPWlkpYnP3Ypj4EGy9Tizhk3t8vHEIn6zO4nY2EfMkjJ43v3F34xTr5zYlR8IwPrdYRM93LnnPfaeu7u7hL2y3QF0ladZ8tJmKGxMcrJ13dne2dnB9Wta4b4VlfptTRDaIR2aZ1Arff29c9Y+R/jrgf0KSBJQcWRY1KwsYvwzYvPfNFRdh6zAxt1Xu0evEmvoUda9WCWkX/zjVLOtPK70uTa9hm/PZVcNKovye+ABBculiNzn7Mfe0vQ24opXQaXmvrvhJmJ2Ed94XP31HEWdbv7lVVpBozTFpN50Mu5Pnp/oxOftHQ9fl4EfXbNoDwQd8pXIBS9cU0TOftgEcS4ABfKgxx//7ztq3eHLzqn/v76Tdhmu2sjJGEkaBDc7FX3Iws+cwfm8CIeuudQ0C34Tq51B6QfhEbo4MRURMH/mrGr7E+4FSdEr0OPKos62Hkh+JO7DjsZZwOLTrptA49Q6T2FTM/1cPHjFAhv+lpynuCTeRtMM0KKUzLrnPlFrbZl0A8hD67zUdQBGPVz2OrjE7N8NYIpc5cV8miQVK7sERtk8g7HkGZE08Ehbu9h2Hre36YjLh4zb0eE6zFf6cjy1b4sXUXrolUqQkZMqhhm5kZh92X7vAYU3ftasBrKbAhNrG8Tc614S/+1Sj98ZDWyv7i6dihCGl06iGYcaOhepCTuhq8EipM8NJHG8W0td1f2azbSNEIfhWCmCaMNiAmiA9YT9WlCn6pyjyY8Sf624of1JHzysq8iuIwwnO5cyQGufKViH/k5YgXaVB9sIzj1Rt8q4nYs3jIWby67TBHMf/7DSoG/snM+aS2osncDGo1ODdlU5sXXotjH7T+ciiq4P1jGKPSS6bBlvHj1dXgPc3qfa4dguP8aNQpkhqFWMGfCUBk+710lMbV+CO/s9ZoBmn29XTRXKB6SJKpFfYfXpV/S6z9z4BPCZaSwtlaBDZfTcQh/ccpvfyV2av/KtRHGGIlTvQkXcQdIOBKM7qPIBeOsDanBWfDKozG/IGyn5q/POIbKwJFQdb6qBPhmSHayVXkI7tjC+bI8aNn1VoYOv4hNdAHMonBn80yqqHXU9ry713q7pg3dTBv3Hj4Tf7BzYgekNqlNfvWh986Thm+cz8ezVkDWZo3bdX8g3/93JgetSRGtpROKlo2iUc4TSmatUfBKPRrIOBgnnzAUOAhpVrz4uRAyRP4EUVTz/wvxX+Oeibm5FM71dzXm8wPEIujvesgy+DYRHowuAx/9Iyo+1htqHLsBSqjMnXf6daioDR/YfiIukgyVUNdPn5c4DaX9gZ7b8kyZlaL5MN6kr6cxOGife3c2nMOE7+pGf1F9ybee7+Yx15D/WPtBCJfwGuS+L1Prl6Wk4odb4W5BzGfaLQqK5TT2IuYHVcgXNU/TffR38ovv3wWTNyAuHkgyrAvO+BmQocajZlK4aefaukr5HRJ2keYzRGN6z51DLbEzQ6F0c7y9EuHpVzFEuKY/R42egVexxjGnr5p0LT/WBKe50svi6TULzARP+ypMb5rvCokoxRqMFod10lTj5UkLU1Ldyv/OG8aVRIbfg0mXV+7Pg9c9Ku3dUNXY1FoUpzvqEersOEYw+eIIU817zhQjEPOvV90MU5c39+zSrb+OpqGaHOxljJqklw4VE8JHz9KjRg+FOgOYIqor1sAcEWe/Ni6xxnDuH0q3Zmw0kYcob/fVYLBkAsNQa4LoHAZEu88eYDc41TFKmzAwGAxcVlb2dnRzW81C1NVVUjKiKrKg2qHqyUvbIu1BcubwTWVB9cqVE8E4jxWQR9tdqPpyy9GY0OkfvNhf6q2unLqcVpHGeml/IB/Oym3T1AMcNOSvN4irjLA/9JL11Hh0wftraYqrffTPqFJT3+UwG53mU4udIwXbTpq47t0Spq+Om7EH0naV43K2V1vi8WBkh/5le37YWOQISe5J021YfbVATpAvmi1ghz84r64LwrgwoeQ57MlqZxc+77Qris5Qa23rfaa4AtyaV8DTQh8hCYPgdsjG9GY+dG8Akn7Rfpgr/QnVgrxPcP30jy1bRDyFm6dIA5n2I3wE+AnYca7RdRPp98iyS+8oxhxtW49jTycM1KSJkT9Cr7u9Cen+GiZCm+WleJr8bn6MnD49hj+w/+1L1lVWuNbHO7l29CyW+mUad/hVz8oDPYlSSgpHfmm9i8QIm2hEKXRZaugZ3KAKnxkdPRGKhx4X7PLajpB1SUYGH9iXKhF+hOTso+pRD8m7rlshZ0IO1A8YGIJO8ei+650ldx+GFfy4yA9Dn+P61vP7tA+5qJMbAZx01X53UlomoT95PXCgcJg1UteDpzxUxgERmvmUx2iDgh+ioWLMY3QM9Y6ElSbVyVKThya6wrM6mGeEOQToXx9j35PqCoovcdouoFy9zv07xjf4FoP+JMtZ76UBPzG+VdJkSLWP1VvU4Or5Iyd1szaFodRlHHetmThxkf6RjMFsyvbeTmw5SRUOQ43b/9p/JrYVER8fj4tuBX7uqm2Al05DdtDJy2D733TQth3ut/x4270R3jOuJ1ruwjdjCXWMYN23hzY8zSOz4H53dmoTQ8TrD2zT6jrM8mVUk+CsBOGXOgn7El7JLxmZdu6Cb8Y2eqfl9wpYXl2shU3QyWIA8uCc5JbOwsWvn6Bl+rMx7iahT070JJXp7W/5lRy2C5hL2pqG9QiozoGfvnii3sSZSLySv8Lm46ViVb0M0rAe/GAErZ9L6g8N8CW+hj7T89i6svOehASGRYUupQWuclcaLfrXLoEkVJuUrNailG62wDauDIDPhK6Aw+sD/sL43l7k1Mm7gIbzoD+P6OygkbcDjvxhFwrGRfU7BCOPujTpKeK1SZz3g4YEy7cw8/PMo+8lIT/3Db0RJ437YqGkNj5vYEXuudlpXdwWCMsE2aJnGW1X18PDTU5Ga7h8R8RPIpAj6xa6iuO8SSHr+emri0SOr4G+xDEaHays5tC+zFUyjcw8XaPgQKqh2KBws2wyNAXp3Nd8JZnT0qiBwvV5id7RVQaxATPrANRXtZLLougHWkwYR7JjkfQHPxRbRzRD2UPBfS/4JcPqmy6igZBVlo7QWyr1dSdZTFpUUTB1skzjbxPmLxnxQDzD/1fYO0BtvYy+foZuvu7htG5MfUevc3tI8+GnwszGBxRICoJUyfx3tShr05NWFL6HdMk8pbRD/E3k+kd1G0l6qfIlKYT7j2GVU/y5STfsbh3XnW4afIw9ZDqvA+yvtGrsHxLscyP+IFTlCy16XJ+uXCOgZg9CQl3RANlqBZy8qPNB7J+15bTk4VKWR2+LPHM0na6WmdtxLFSo+m4Q7reNA2YC7+AFnCizI+M2GNxvAxQ6zmIv9EB0uW1e8Z39vfl0rMnwtWXSTpj8DlqgnqflZEaV7BsB7LGGuFLPXwc=
*/