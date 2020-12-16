/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ALGORITHM_TRANSFORMATION_10022005_0551)
#define FUSION_ALGORITHM_TRANSFORMATION_10022005_0551

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/transformation/clear.hpp>
#include <boost/fusion/algorithm/transformation/erase.hpp>
#include <boost/fusion/algorithm/transformation/erase_key.hpp>
#include <boost/fusion/algorithm/transformation/filter.hpp>
#include <boost/fusion/algorithm/transformation/filter_if.hpp>
#include <boost/fusion/algorithm/transformation/insert.hpp>
#include <boost/fusion/algorithm/transformation/insert_range.hpp>
#include <boost/fusion/algorithm/transformation/join.hpp> 
#include <boost/fusion/algorithm/transformation/pop_back.hpp>
#include <boost/fusion/algorithm/transformation/pop_front.hpp>
#include <boost/fusion/algorithm/transformation/push_back.hpp>
#include <boost/fusion/algorithm/transformation/push_front.hpp>
#include <boost/fusion/algorithm/transformation/remove.hpp>
#include <boost/fusion/algorithm/transformation/remove_if.hpp>
#include <boost/fusion/algorithm/transformation/replace.hpp>
#include <boost/fusion/algorithm/transformation/replace_if.hpp>
#include <boost/fusion/algorithm/transformation/reverse.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/algorithm/transformation/zip.hpp>
#include <boost/fusion/algorithm/transformation/flatten.hpp>

#endif

/* transformation.hpp
GyumMS4Kq6dWlMcxJgx/cSN+4/eKy6IxYtHHz4vQx7cfD7SD61O+HsurNUYiYz0bsf3L6Ksi2vKoEc/RkF117Bjm8022UBFzlmcTq83Yj8aYQn7ZjEXN/7H7Nzievt8ncXux4Fwwx0aun/fhr99DcpkyxXHOgzKtSEKmYF/t3sYq06+Ul2OVSXN8/HL9koRcwevkaRu5VlFenSmXrpXk+uy3JGTbU9fXLPndK5O+8xTSPTwb1gbuI0yY3sLJCezzKPa5r7iywLgaQ3Yod3cJ+j415+SagJz8xLzeWsq2paByiq6vsLk7am7oLx96L2rf6hnSH8b8E+jXKcbEXmVODsbHmHNDM3OB7G6MokybovFBP5xV9EFE3P4p5f6cUWN0STurneVf+xiCby87y+Sv5w7d4vObltHeKkMLw59eSIbkxmFJnL7j6m3qb2nsN4bqT/46fcNJhqhrMtvGf1/rDGQLybB616Tu1U5yhOKypXeU3xkq3Q52hM/TBt8KyVHp9d/j4nnWUXwxi71Zl4hry6fyzBhjl6dINuUtNe9x5UXF5fzT8VlIY84o0mN3P4yYa1aoraeorSeorZnLQ22dWuSLf66xs6vLNttJWbqebdqYZ9NG+cfVuePnoetGNqx6YvpA8/jbpI0y+OtPv/y+ShrsLcJE2N/0QDtKY8w1vnDZ9N2MiDlPdoTR8uq5YiV9uoTfH8XnwoAcOjfI7j835Vj5+dsRMe5K+ds4rlBbLiZtQltS/wprizGtxTH36x5jaUe2zfyYE8fYCu/zYZsFKkrRmGnbgoScjWFyhlQbJGteDFnzbWQtDcXaCzhiNmT1KdYe32nlJNCGGQ5jx7z/lUytrKoO9UG7DP94nBx9/5q1eUCw0xWn/mTYwZiHWwTsX4sDo8nrH05eQ6zYY8p4tr2i5Q4Rz7a+0POLjzGtMWZzj6uJfG7V3KV3IvplmuW8lvBdYBxmG7Ekac8WVPwB8pvjMPL5Vv2kdy9+bs5bum8WRdw3O3AGzlB523SKnDurZYg1Wu8GB8OUDORopf4LjYzYc6fRbwta72B5JygJ2G0b5UQ8B8hntM0zvP1c2T80viZzIjVXRo0N9Zf6ofJv9s4Gzqoxj+NXU6TCSO9SI1mlMHoTxQ4q04uMajXRmpmaqRmNmWtmUhLGbghhrBAmBqkhLyErhFnytrKGjUIxCKFdw2aF2P2ee3/3nnPuOWfuS6P2Ze7n8/98u9Nzn+f/vJznPOc5z///L50RMV62tHO30U7Zs/FttEO20bPbO+3kU/lHhluZmO1H9z2tcs26Ouz2c9t72u2TyN1mvGLPXWszntshwk+D9uRqQ3rYHnvlpiGGdrHWdUMHZ3+fjVL1LmXE29+TB7v3d35HZ3+3Ne4LeznLTKS/9+3k7O+CBvq73kWfduiT7aoPbhoS1EX9zdrF3U/D7E7OcZfND6pc9Ih33E0eHH3chfTY2sk5JvYdyP0wrIfNTT+jInY9OnvMAXM7O/tgX2P/uaVrmRoVsfupmOgyB3zYwJho3sWpzzMDmJM89GFUJKRLqC8eM8eErV0qujjHRPJA/u6mh2ajeK7RznHMRy0PdI6L/GOYj8K6ZPKCKajI8LETxk2K06/LTwPtY+MklVt5oLMvFh9rLCY9yk3At8skl/HxmsO3i9kWvbo6++Uc2iLNS6c4/ar8NDB6v4SeeZYcFMwhW2u8s6DhW8T/dQ/5Fgk830X1JWKsT5b8w7JnyfdyfT/X+EMj+BvRmscSW0TPsxFrmXSX5740+1pf62znPmhfGqHqIHRB8c8DbaA2jHhuNNKmka4SMeq03zektTy7aa3ot6wVJWbb13YLNuCNavsKtX3q38M=
*/