
#ifndef BOOST_MPL_SET_SET10_HPP_INCLUDED
#define BOOST_MPL_SET_SET10_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/set/set0.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set10.hpp
#   include <boost/mpl/set/aux_/include_preprocessed.hpp>

#else

#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, 10, <boost/mpl/set/aux_/numbered.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_SET_SET10_HPP_INCLUDED

/* set10.hpp
ic0VHME2DG1PLuffP1LeXbm7B3fS3lRJHhLF1dW4oS1KxT1/W21+mc+lu3J1xd5IHVepDoNl8y/MLWfNl+PVKlXgdrmVy1EYrGmebljovYz9dL3/nngb+Q+oVv8bmm+9OOMJYnj9+UZWg7I57vlVdzPzdiPUu8m989v4dJYA43U6k5Nl+qIn32eVAkuH5EKkK523jNfM2fjcXnaTlaWxzgEGx33LLiI64F0DYB2Zjgn8LJ8N06WOTCqv2j9A5hSICt+7dZX1b5HTvCZ+/ju2Rh+iZQ57hVZbVwOKejVuemV2A8TOntq/mwGzv+Am/FfJdQ1Bbk/RMT5qRapHLgZKlZxJ3TZeUbT7IpEiggRkXV9VXG6bfjyuFXwL0VA6uukr60c+Va3MuRjd/PEzyAQODXBaGqy7p1F2dn3PL64XsRTf/jt9aDzB1NdeULGBscX39DnyWq6fr1N9hX7Nm9gdGAWvkIDu3fEd/xHFntjo6Bg0YyOju8I3rtiUk/1wv1ps8j/QeA/GUMoNuKVEgWSBolwLjCDz9V42k68sGaGlIExm1AXdtJUqy3pX5nf1YaemYcMG+fg0KZug97rpoa+vvxX8f7UobieNJlSvMbmuP9vM/NkYGRVROmlpSiQ3o7GnRpCBNKd1YOznU+d3eEUEcvfCbw8PCoLFZqMiP31y+wqvq0L25PtCqk9oQNufjlQrj1zgQGQ/AfcFUuIuLcREMgjH97Hq2ANYAWR/W9LI/tss81dHxwsOiw5+gpik5OSkhKMMvCUnJaGV+OCb5ADhSTpRn/ThNyTbO5aXlZOIi4y7xKS++bAx6C4N31cBGBbU24DX7aRy77r+1fkeXgm7hxsbB0fMBwGh1GgKhsmF2tBvWqbHmTeNRy4UNxRtyb3R9+uXU2uNcBDmQajwWXfzkNQtpXL4lj8wN4VXFtpsNHGlLzGa79NgXdLBaPKxMXt4J+yj62K9EAyeBk0mjJ8WFq0q98BfXqHA2aK7nHije7JL3mL/KdAQwWNYQ69ghRp5/MHtBvfg2poaXtYQ3rRo2dK7+SRESPktMRHB1W19SRi1tRvONsmFf20ey1HGoW6/u4FtXvlksRmeQP28YaX3Rqf9ppZ3T2bmUbbcD6wtf4PDjUVVtKUVbudH8RyDCzAAB6BhtNVed3v8BWC1hf6T1w2eoQQ/Mds4MdmMN4tzpUMoUIeDtAU7xQpwxw9xtFEF9+xhtWVlbBMjlcx3blrwhl8qN3A4nLbGzNbOUIc7pTtFStG4KM+wNg1C8kw/+4GiqLHzQ1+ssKhuWkxTvWv2YZ2Cjye9SoyuLOfeT/EXp0B4jyBc+eREHBkDpUOqXz+fhxMTE1UfIHcH0fe44AXAbE2vx//azf8LCe0H/MEDSNuSKUQwys7849xhRcU/4L8xJdiHng9cmvYKlenuzD1Xc4pFDxe8TFBEsVdODCQoPAwXdsaoxXvSQAcKyF43ebIYt6vj0Wg8HALKoHA3OfLzY+jhzG46TkgkeRUKBbG0jDO/tp5wp2QnM8sj0HjX36dw33bLBJzS+WyKGjN7he9Rfv+0gQ4eGhgKv1x3myVMSHfbXm0Zd1xdzmLXRV8y/tYXOfUWhnZcEXP7KPq1VXV1bbHtVoRufOptfEosi1vMl76puUhqeuiFjnvqB/f8scfUcM+g70munvK6pVSSvV7yBGxZmxilxha8wciovQQh2elE15bx/XDPRnL2MOmN0Rp11dJde7vjrt9VvGP4JTBoOTd59eRdjSNX+1FRiaOiFv8t/MqR2q9k/CmadfvFaNwtfWu7O0K5vHv/cvhPpQo8Fi8V6k3kvXXqgeeRlN19oZT1y2gQNztdcV04dZbWW4Ai7oFEiV+gC9NLcWd0QBTuX5WlfqnP2hJIn0+Ub7ZxKAQf6LESM7lgl/2PdTvO6bLbhXYysmKFV1Muk5yXP3lnVR/iJsffG+581Lxk6HHaNtI3N1PkHTK34AtVbEu44VIyPxC/oiYp2j9zM7yGKEnybke3TEO74m9QyJMxUVg9FTFeI2sVyZ2cyH+8nP8IXdy/L5gmBUBB0SII6Wy1T/nJeyHv9A679ZZGN3M/cDaQ4nMIavgI8f55G6gwNZMFQENq4SPc0M+wdlztNZZkvfx8u1pdscHocgMR/7E5A/eru3h3PFKFomDLsO+5XzLsqpVbZmkkwLvnMCPFj+ByuyNh/wDCr/K4Pxh+PAWhLZpm210qkIXtlVn+xsW2zJjN8FND+jPItQYU93QEWl9BnD8S9VApTcU5dYSu0W1puI3zDjfmupqErwCk8D+dohYV9NykptMDGsEvbXRUk+KcB1wGryNLHL5U/B66zqa1+AkwrN+qlDSw3CCXNfLesbeGQbfdSEPT6kFVUT0m5D8wP++Tqc7NzbJCWGwH0Y/TDz+zgXZNWrMxOHCcf8Uh98KL4en/GJQJyXrcX5BgBcsqbO4LDmKNm3bFQl7M2dqh3DSD/s057VMx24CIGoGRGvwTln9vRptLQm8XLxZUyLuk9nPcRcjxjMqM4bzUyDJutkRnpDfqHwX8JiBubo8uO1B6X5tjvj/0Hgo/7NptlOY7Tper7oICFbzVn6/rm/XQn3aWFKTGw7O/uEmnYzJzSAPwLDCIWUngPSu5Z8o6wIvAezY8fBOGGiih2u3vz+f9PgZDd4QFHTpYzMUPIfZn6+TqmczhDnde2nXlLb0Xx/ryf4vIxR5VXTJ/i7iALMvD+6ZnTI3wInhPYicSdGIj6mSqlkwFhgHg5hTBckPpqs+J9Sj0M7j/C/HhvVgcIfeqEYUUGEA3NZEoKh4+7+0uuAudg1vEigFwZ7gF7U3OMsXAvwn1qcg5LkAmznqfySkhDMb2m3r6KISkocnpqKvffz6W3nsewM9BIcXP7E1iTYJTcTlbgUZY4pqB5mx1E+/bOZIg7DPmEWtmKGr81D3cz5rfDx6EBwkZwPRcORm+E4M9oaBwsJa26hG93AyDyghBUfOAmyCDGpPnR5jxQYrOvdyW3rGL0l4zmKVKee89h8DfPJnNEOiyw+DVv+b9McTNDaBHkg9gCk2RU1eWz0LC69WNnk3QYjAo4b1LonxG2cIzD4XiwZRBwZHgkALNT/tKTeFrz7+Yjz606Hri0lBZOUfeZXe0ONMsQ4F97wBCLXNC+boItET8h8F5gA+miYQY5/5iVZKWICchWVblNTaQy+n6ITRxdsJ6fhnNY7liuvwBdYR8dc02U7bXxx/1Umggwe/i4kIqDi7xt14B7Udpgn4G48SiUJOGEXWJWBFKJJbb7k+jtBQJIdRYTxx1f1CbqsSVzoo7889T+RKcTMSIW241Xy1+Ez+oTtmeGGGxn194ADR6QyPJKcWXO+zPkVin6JOzyOumCCr5Ewp5TXMpKnGeX6G6unrTXwqouX50fJ8AbYvDbls1fn1TTk/TW3vIsr0hcw1/pX/GIrTFZ6dQM1kSstaHVSOTv1O7OF3le//VeaU6PNSsPFS9BgKdjGEYwP15qcxLXeKv+G1jZEFNgK7H+gZ77HpuXMBfuf72RRBfmUjewJ3WadVSnf/Z6a/laVnBHcH5jFGQg+dpF5aNdNu1U0+JbW0WBi2nIFuYOd9flM252ioYUdhhVUuxTNBca8FLzPDQ8LjlCuZ1fb3ZxgYFfX8n87ZiDp5lGKzV9T+QgN5k+UT0wnp3Dd9u83/7MtLM5c31AJNIyAm4nAlsgyyd2eIWXSzf1z1fOpBF7QFLNh6e3oe7OZTJpiAn17t777byUfbcPfj6QNl6dbF74EmvbTHKPGo99HYRX1C+u8SAMyUu3JOIlLGd/gyJJFTP9SQ+PdWVtDGcROEpHlaYpQJlHrWy5nS2MVy82th87tkvKBOzMbVcrJlrCK7Vh2oyaR8wLaDCltMLNx6dKlDLDejt+wyZfNA99g40Xi+YlCFC6bpeYszfu0blcZxggBzrDZSllENk/eJ2kwjo+qCF6ya1bCD9lG3t/dBK+IUpjLGJt+yoLS/UpWmc8SUYHbaaB8wJ4dIXcuOVhGRBPmZstxKi188k9GMvWcxkEYxusx1mdql5W3olNkY428H+JBRy70H2WRae7GFexGHHvNSRPrMLqFQN5qwlVrMLmgXq7EoOc9iDM4GfJpV94nT3MF8ikKv4FnbsStXaFhvkPhWiFXG/hKENXXiej5mCmMfyFYCax/IXgNZ9TDsdMfwtCvnMI0pFLMqlyfu8rX3+qJV6snz+YPZ4Xb1tPFL0KPbwbtky8fC25G7H4W7/8DblbtfxcOiWmqQ19/syeR4LBRtbTbWU6OnZ8vggQbtZTUvz/j5zJ/qQeGooXLF7Wcq1JvFYV6tc9a1O7c7Arpv1N3zVPVcBn0apn0yV6RUp3TCz6eOpk2mlNValfYZVE7XpNphU3vXbptUfV45Nd7YDMJu45Eapn4bVIKVonYBxfK9+UJ6KUG77hOv0tqh7S07t2h5l1enz5aKWsJNN+Wc35rGTVfmentC1ZXLD3C7ieH2sD4b1UPdvVpNE3d5CJIJzDpy+ZRzsYJnAOwe168jsfYpbvnm5aUJgvACoTlrAfG3JIADnID881/r0PQIiPeD5hjuBzcibfapEm/0P9zJ1NgbgalzduFVZW2i62XrbS3B3y1xf3zhkateriCZ2nf1d8nh9T/Heeitm6Hd427gCo66BzYqeA+iJYP67R/x1Fi2cVU/XUPr8eIMF6Tt1I67EVXe40JfAI30fefZ1pG7/qGA1wSZXQvsmkin1H4XI1jgqqa2y5yFbpm5AEB83gHx9wNc+gpGFaOwCpiOzCQjHMN/6s/VGs2zq7G8Q1m42YQm/OvZ7nYO3+bUJPPRZ1zrbOK80N2AN/n721aDi8V1d5CDU7+Xe+V5pe3IlnW/+rrisVW/rnrooRsRIiOI6pYiRLLZQBJPHSwiP5eOM6IMhpgs4kEcJwgQjEBCyoxAijeeXu6ya1cdbb7p63qa7G4GN99z69s7q8Myefkwxrr56+t5uPnIxrjK/Pm5JeYNmMWqB2haitll14fiTQewYgAZUqxBOyYRYVdqtiIHquEzc1W9AlSJ39nG1Z+4x2608/PE6/5iLXvXXT4CbsrkMyCkGX/+6OQ2mplYKvDq0jqsu0R8exFXTroJb5zjAux7pcJiWnYVS9CgLhk3+zHtTQtdwH5kjZw5wiYdMsnjOk/eByTAemaPhhsxmYMSZYhzdX2BkU7GA/3awNOtiCRUphQ3AOR3YdQetyc6OdZsNbrvpRoBERyOc8GZH6kohvBlwIH6nHnQXxaKhZxkcVcbeB2gieutDJ9BQBk6vhWqmMsWNq5BkgtFw4gFF6oP1Nqbc8VqC+tJyat3zBGLMErWduEKMp0Yj+OxAyfeUxmOYRT/dEbUBTKKbICiNROfjkBvBQSE52tA9IUDDv0491PPJh5GM01XcvFYBTqyiaiidfePjkDk5ORB3BvhvAYV76TroX7SE+Ph/Vr+y9x1OubgYvPYS0cL8mirFjDrxGeP9lWJ4G5ACEZOwoFgyYeFCA5MurYp2o1C4dim5o63Oz8ckHQV9OvButmNINbm+JiFNc1jTYr0Q0nChcivklI7b9/a1fZV424JCFHSZkkDz2FixUIX3yyhj+wO3jI5OjPLxWVFRXxPvm4iBZycS+72RolWZy8emp4Xt97X/uyX+iY18vHvSZ5mQjJTTFvkqNFBSTSr4ORdUUlLKKykBq724yc+/wczQ2RrNzMUL/CwA9PbU8D/Sys6PVI5MpmoxfT9gdZWQOn39YFlbW7vtrkfw7rYe3vb+on1rvbPKf6yCWRUPA8NJS0hInLXTbg8wOe/dJSUBYNbRRMBKzIEDS+9MQ462UA3ZrI309Iy8PfHfkmrGSQhhTKPgELERgPxPWX9Xsmgn9Ij8HiEbest4yGhvtw/0I3VbmKEwD1SpWov2gvaeUjV6M1NXceis3sJufbyW58fwQoKMS6NgedchM2krbL+c18LoE4mJj5YtObFuSbVbUf2xsbA2vfi9fzrViUZklXcKKjp8jnOqMow0GQXpGUt8+bt/w+4rlc2xYGCxAlkcPGTb8vPTtX0v2mt7Se1gSygT+x0SsVz7tupS0zd9Zbx1fHxOr+q92kIrK+ElpTVmJ+rgGXvnWb9sfHxGi+UVQe1iy8TArvVy7QQFK3kgFR4e22l7MzuEB5cHB8lYWAKKbZ2fGE2UHzCfHYlB7sYaAkaT4XGDSEcMhK+9lko9euczw9xixyKmxhNdQU1VlEeEG7Nwhe7hjnSzEuLmSj12ZiMUzUAAyup00sLS0sIaGonaOqg3+B6zEcDsAg+PCQkfcrtr5RNqo/hEqurk1SJEudcyTMyg5+PQQ/evGe7v7+/iFNzwXSMjM3nPpuZSq2UTFQKyZCF9EMETRvZfrBLS/y2J6MA/G80+Nl9yb6XLox7LVlSoSeXTZy2dRB6K+rBm9LVPH0yfsjpwqlL88xASUkYRC11d5n62R8VI5H9EGpXN7kjd4/SsXI1XXbaL/jeZVXKiNDcnh0dAbAdvGHkYGt2+u7bWjzq4a21lVQPojhixC4fNrRIwpGOHhYUV+CtDsMnvNJM3mCe0sMyz5Mvpgxw9HmWceIIppTqDTcC/teggKyrfdSjgY0f7fHssIqVA+lY26sUFJNLaRQBi/yzrvTx07zr+m07ps+DYjgsf8i2qsB4+HlW1RTLUKdLcxKTEwiTEuIQjG4HR/zj06yoeraVzOrdvSJxsDqOqIlwXgTBLZuY+aH8dPmt+dWa/Z99+iw6HS2/zD+8WoIo/fctLryJoSTnazNrT3vqx1T8okmAJYL9Pl09eYALKWZ7bwRo1cKdzCT98xPIs92V1u7uLPyRJVoZcKFVIhPHrpKw8jn1hQOvvfO47fcXwpLn93tHXhcVjF3FoZpAOPNdxCYbxg658juX9B+L6+DJ0+mTV8z6OJZxxAVZOoVjEkrhIWmPHM73e+TyYmzyQ6c+NHnY4DN+FAohFZ/B4eo0oupQiU1ZWFlE69mKebcXjUYLcP2Xu/uh/bAP55TCaCQpXVEWGSoGPRFV3sVm9BZHZhr52Pxb3fYMD7OrsZjwGDln8vLm/CQ2rKC0zo5pbPNiW8tyO27hdkZscnHK3Co71TcZhUjbaY1vHZnbKKmkJe3srm9SRilOvwSZnWcrr86Mb3dq1a+ngqVrriJbG7cdcqaVfc762xeuIOryhwB5jXnk4gEbHwEEv3BMh5r5jZm4O29nOY6TjXpx2exMSEr6jJAAALP/TPz+j2s9npdVR+kgcXQPIustCTCL2+xPWJTybZ3SfjmXzYk6Gku0huLieKqyY3Rvbe2VtBuamWk03GtHNz7XaMESMREfl77xVMzPddT8QeyL3g2+ihDnQA2q0ICMPh+72CVKNxm9mK29vwIbvPhaqhD+/AyBZQuDhs14TmGaxx1xbacB2jtUdQLAAMnsEkoxjMTFAPu9HzizQmAw+C1CwsN3Olyf/pTjF3cT895iFHoQE6ZljSay4Dx0Y9YbI1JmpA9Zf+N4qXwO3OPnp0N/Ck/LBjvZNsJ33HgwwrpduTBCU39h1vKD8wsffop7Mg91dyM/W1oCF86bY6ADCm7vY9YCJs7zY9QFn3jO4AVDCEkiLRlilaJbMimMTRWYd8Hg8KDDnZNKOiTWnirYqvndzpfZOy3oY0AlX6gT6iH8qrp7gF95h7qAVWAKlFqtOFREy8/AFZuDyTbryPmzCnF3g3ra50uO2xR2PqWbHxgjMOLryxVe1ZUgvdhVO3BH/1GMLJJa1LavJ5ZqtQStKpEst1gt6LZAci7xO0S+Gvk7TAQjVyL6Lrtlux1O29e7jal9NBjhLqjGBMx32bGV3wE6s0cM/0Ql0cliRhthke3UXIGfWH0CiyqT7d2iQOGSZxRdCabbZMJoZIFJNJHrdmn9Ln0r2pgjE52IlBDTFsTg0jfU7vOGuzBSOvCnmmovtPEph4Kx04b6zKfXLKeAfgRn1bJnARZlR7T/yoMYrXfvEDRmymon38rlBc0IU+zlIIX8VF/f47m4+i/vmtCFeBRn3LclB8Q7P73jpgWvIiu1vlqi0mHL9/zym66nP8tdNS72lzwbmVsN8XRvt2btRq5GlHFQtWzx4kAjMTAmERcNsRbUMTMpAplIp7flYsGKYbNw1zYFNWtAKnPPuZ1UDfV3BHxR0I8aIXPk7l9CcoJbztRhBo6XO4WvWwzYwbxLoNgFfRjKDWPJSUW/6Kx93EqgWxjgnZ6gplwa/b2Wn7Rb5v1N71udpQ0NFg9fVK0FLGA9o1D4wcpsp4YTaBLM3WUzbFy1hgE9M29+1Y8KpbhgSrfKp7R6rCxQOa8idHtfeI5x1oVidrusxnuxjOQINbJ8QneD03nT6VXzS8FWNIgV11vA3nWIN1acQzJtCJnwf239OKBC/1YgsHC+LwWpFNsU9j8VoBU/S/Gsb24JtCYUyoP1HFNGMmhXJNPRpTVyPDWFDZANmIxj0SFOn7STuafS4Kcn22sf9IRo0bMXvUYbEMNBCQG2FHqAlbTc+nTCER4wVE3jtiWCP/ox4buuXtocs1m4VZumjIgbBFvhELqgFTy8sEESysH4yBkH2qUAdh5sf1aXGfDRyJQx3SveADCsfpxdWUHRILs4dkqUGjUKqmUd1SAzYrh8+tMJeQ/PsLxqAFGmGY1Me71uOnLl7fhaWk0P4QgqM8xkETd+3GZNgjz26gxY7ftuzsErLC5nSJSKkJwXBZB0sx3JAstntifakkBmTfBV2cQB5YLAtwGdElHHuuauCDJK1Jh/I0RU1UuaaaEwv65kVcp9h56J0EpV3octB+4C8GBd2HZRLcMRdJkEso+qJMS3G4aKNFJDXAYuIuMk7kSdsS0Z0U0+MyMrC4SLvIisj4/1HweeuTp/DTYG4FJurzD3QeCHBj9t+786cgXW735qLl3+c6tBlVSWs6Uit0+Xmv8JKO7++Q1yG+Zu6Eu6JJlfxAT87MYFGuY2J+YKdoz2Wy6lzd+5cMmJT6DMADYXX0nQPQahJXvmwF4OLlZ67qvN2d12E9+BDFibAc1D+A2fwIcsj+VtnvRmXT0R62mNNGlbVGcLpe5D5YzooORHqxWq6n9DOkLWSMvA1mBFwl/sCOGf8IpB/fC4LfkCLeKQ+6mn/cOxo4TDewPReSG2yxqy3OzS3tCQ=
*/