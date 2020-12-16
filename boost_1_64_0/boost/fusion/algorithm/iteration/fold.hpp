/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_ALGORITHM_ITERATION_FOLD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_FOLD_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/fold_fwd.hpp>
#include <boost/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/add_reference.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/algorithm/iteration/detail/preprocessed/fold.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/preprocessed/fold.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#include <boost/fusion/algorithm/iteration/detail/fold.hpp>

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#include <boost/fusion/algorithm/iteration/detail/segmented_fold.hpp>

#endif

/* fold.hpp
nmMZV7qWPPQ9/ynFjYnQd630zVBbjkZ+j74rSG/qq7xi9H+ie4CjLQfrvhCp23bpNqu9/b6XuY95Pr0VYpR5mdHPq2260Zbms0IsPlMM/Vq6tGdyeC4NZGWbP1JlN5+p95ITkSuMa8qhC/klqEOHoA5aGxSUls7kgUlpO4X/XjozZH+X4rr+c67VzespEC7cVq+V+zrb+ErqVeuoV2CuSKhealvL3GEfg2P2c47Bq9Eh+WmLDrpeotvjeI9BzaeyRyQ/jb/MQDm0UXu7n4C1+7n7iCl/uscv7CMmWP7kZKetiB8dsx8OlG8OeutcF0fbBO+juVNMWyXn3GHqw0c+BgZqbktFZqBPsps+6q9YfGjEo4/mQut9xNZnG6XjbLVZKXKNYV8T7LPcvMK8srysvNnx+CDi2cm2vs3UPRldyUjXXdg+lh0Ss79NexfZPjcnzQbE6NNBz6CTeU8nT9k5B3J12oFPPiB0voxRBRfA66hbRTCf3GKjXoF1V/R4/IaN/VvPWmzspYffsY6SHa3HPb3c5f4932uNZsuD8W7ex8xnA0vfp4TzyGUiNH1tYMuqvxdPLVO71vG3XrRPjtEPRr1MHxHKxx+O279R7X5Fp+D1317pK4YEv+ea323tv0YHUg4xXnnCbvAPRvvXmO2veTIGnw6sk1zWU/ku9wS/R9vPdlkvltuvDY+1sa4jx3OaV184+9Nop67PBdvpBrXbXH1fqO8/R3y/6nl7uy/V9xsj2nm+7PmLNc+cg9xMmvI1gfQE8s0rKZialVNadHTMaydrm3g/r5N+T+f4TIGtA2OOtajS9nKMT7s9ZbsO7nN3fWCu1ManZdpu7HnS6h9hRQf3ebsqQhdN2Y2qh8d8rXbi7x3dbb6TX/jlbL5XdnS3+U57YffYfA/t5GrzjZHDrrH5Pkl61Lr4JMgawF699FB8ch4ch48dP/K0sYm0DfdSR9tc3Na7bcpkn3+Txsf1yC3GIf4XAzoZryXy86bOyDJmwAKcH8bzPDW/nTkm97Wtz/yB+SktWIbvINIZ36fpe/IB9utrqGzlv5COn0jHmggdNXElpF8H23qCnPRcbOjdK0Lvli/Z9R4d8f1CvqsetraeJ9v4jdpnXA9vox71L6keoRoY9zleHnGFR11nGL5Ibn7F7qfIL311j9G9zDFHu68tHG3g7Rsow3ovk766H/Ib5zxv+slgXaG/pdvWdVqDeMz922BtMy/b4d1n4+xuO+xlm+xlE+1lk+tl++xl4xy/jbC7za+XrbSX7W38ttLuNs7x21C724zHb7Mcr22yl231SwGb5VZ/rx716Zo5STfd8eijs/aa8/eGbZMH+/ReFY5VzNTmkKoFPn+TLd9XMBXWy6bva4utZ5V+f7Z+b7X1nKDf/wYeLhusfrLBSoOZcJJssKQP7xO99flO+X0vfX6QPj9aYs9W6PdLXGLPZun32bA/nCLbsalwOMyFU2CeYs9OU0zf6fAqmC+bwQJ4BzzH1Jv3aN56f6xyP5Hen0rvz8x25P2VdzuO1O9HqR1Hqx3HqB1PVTuODceq1XskmOQSq/ZI5TcAHg8HyhZoECyEx8BL4GDZAh0LH4bHwafgEPgaHArfgsfDL+AJcBv8NfwepsGf4YlmO/Fux7udnpReq9VOT6udnjF/z7sV79+v0e9f1O9f0u9ftrRzuX4/09HOssGDj8FU+Ec4QbF9M+ET0A+fDNtW612D3kFURdhW/0oxgQ+XTVMfOAz2hYXwCFgJj4RLZOP/MkyFX8F+cBtkrEp/7ffDRS76H6vyhqq841XeCdI7Dd4AT4ThmMlPesdMniMbywvhr+FcOFWxGKfDcl0fl8IbZCt2o2zFQvk=
*/