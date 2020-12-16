/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REMOVE_IF_07162005_0818)
#define FUSION_REMOVE_IF_07162005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct remove_if
        {
            typedef filter_view<Sequence, mpl::not_<Pred> > type;
        };
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::remove_if<Sequence const, Pred>::type
    remove_if(Sequence const& seq)
    {
        typedef typename result_of::remove_if<Sequence const, Pred>::type result_type;
        return result_type(seq);
    }
}}

#endif


/* remove_if.hpp
X5jKxyFfmMrHTSpsvMrHTl+YysdmX5jKx3pfmMpHiS9M5SPfF6byscQXpvIxxxem8jHFF6byEe8LU/kYpsISVD76+MJUPrr6wlQ+2vjCVD4+O0+FqXz82Rem8vGWL0zl46gvTOXjaV+YyscjvjCVj7tUWLzKxy2+MJWPXb4wlY+tvjCVj42+MJWPtb4wlQ+7L0zlY5kvTOVjvi9M5WOaLywuTHwOklTYRPfvker3BPfvAep3ivt3pPqd7P7dQf1Ocv/+ar2qu2r+s7vMf8p8C+MIP9zZ0K1nPf84z3oOdX7sg8la+BvRNT/J3Vy598Q/1/1x8OTrzmnZs5ur28p7i7zHpPJ7Pv/tgjIvWx0Je8OJsC+cBfvDhXAgPBvaYDEcAithNLwIDodXwhi4B46Ct8Ex8F44Fv4CxsHfwAT4CkyE78Bk+DGcAL+Ck2AHjJ0MI+FUOACmwpFwOkyCM+E0OBvOh2lwGZwL7TAdroUZcCPMhFvhIrgLZsFb4JnwLpgNH4HL4dMwBx6F58C3YB78M1wBP4OFsA1luBJ2hUWwD1wNh8ESGA/L4BS4Fs6BFXAJrIT58FxYAtfD9fB8uBluhDvhhfAmeBE8BC+BD8LN8Al4GXweboWvwyvg+/BK+He4HX4Dd8KO2l49sBvcBXvD6+FguAeOgjfA8fAmOBneDGfBW2AG/ClcCm+DefAALIaHYDm8A54P74EXw3thKmxgHFHGGv3HEY8huvFD/ZihjBVajhMGGh9U44FVSKAxQBn/04/9Gcf49ON7xrE9xvT0Y3nmMbwvEcPYncW4nXHMTtafIYzRqfE5GZeT8Tg1Didjb42Pu30EZazNNM7GGBvjawg0j6mFNp6mHz9j7EyNmzFeZjVO1ugYWYDxMRkba3xcTMbEGAOzGv8KfuxrB5wAsxDvONdhxDi+9SX8EjKe5TeOlaoxTY1bMWalH6/yH6v69MP/vnGl7+v7v7yi+d//ffkev0PzG6QTZDTXvjK/0uEi6coKl/vf7uTfjrj/DXWu/NLC/PJC93pz/u1u/u1EveffXPkrHHbCtfGExaPDlG9nF3nWVsJB0AlrUxAnz2UZT8hatGRxluZrG6Sf7fvl7rjKxz5P5xcEPH61KmylI39VhfKrfZ9E8PtTPkVVMDrC/X6bX2L3hFWruPnlq+I9YVv43a6jhCX4/JHedadH/kuc4rdk9lGaZFh7EId0RUYjPXpw3yqMZVHgsOeXVjqD8HXV+9Eek/SXIpHIIuReyjrCZUwfH8S4xtNuLD+Z0jS7IR2QcOQ+9FVb6svVCjhon/ur3H52VU6jj+VHonOt5NGBdDuVbxIrnZq/aHFho3UqUB2y+edd+X/+yX3PueMG29Lb+/wRu8p9vqIHrDTbFqz/pz79I5J+ONJBdNyvlbdl+u563+zyTuwg62VEZxfRWWOhU/qNJuv01uMHRGc+EoXkIA9qfYZJJ+sEgvADFj9s9lRw3zeDD7DHZr1v9UwZA02Qb99Y5Gfoj1tnoT9X+swgxj69dYr+VumNIixMhZU5Cj3BfuVhE//4nUg/ZBvyCNc7dfYUFNkL1njKP+jy+HmkwS/dUP8zLfrQGNXnOV2B2kk4q0Je8NhGvjy/v5Lf9L/uvCV4fYc7y/OhjSdvTng7cepK3dfzfJNMBfFsMLVjyWuRIa9OQ74M61ZUvxfV293fV3med+0io7kPPTp7fGAml7ntU8+Bjob1XNEGP3/yrNLI7uw5k/lZXRqpFmnEWKShySQpu7rOZr/fQ4nU03NJ1+1/O21xRrzm+T9rRpbm9BuCz+8Bne+tXmf2SWaf3zu4Ns9Sp+bwG7y/+YEg/H29dtSLHaORXshw5FGtX1I=
*/