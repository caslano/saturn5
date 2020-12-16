#ifndef BOOST_METAPARSE_V1_CPP11_NTH_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_NTH_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/nth_of_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class K, class... Ps>
      struct nth_of : nth_of_c<K::type::value, Ps...> {};
    }
  }
}

#endif


/* nth_of.hpp
Ax7px/7EuM//DQr3I1NxHhz5Y7l1j8amRFPz8gasZ4wz4eUN6xvrGzy7vmHCK+jVD+XH9eS49pkJPI7LTJ3mr3Vw35E+keFfLy5lD36g0T7UhxiW0jq438EHs3tu/cM019jj7NOlyWCQ+xS8n8N+yNLCD9k2fFv/LLnv8hCfsdPZZyzrctaT9j54pQcfCdb9oqEDfa71bLiPWPu+2wLl9zYi/d6ir8WFbnwzMSYpdGOdeR+OdWOHL628/uRNLeBPEP1hS1zc5UEeeZ85W0Jp9HvrHHfN4HTk34r8+4+T+was+3cRvhJbzu4B44cuaJ8UbD8q9Agfd5fZ9kIeuLUz8dfYtqN46wkzuSMd+AK27djZj+gcnittW8LGQ7jCsfHg5xdty+NRRzot3l7ttfYe0fX36OjCLeNbYOPZn0cM/n77RDtFDIx8FJGD2H8L8+urPDmG+HG8dCrfBxmPb7Qpfbt346fNH2nXZ+Lyjn04zBDBuGdE+q0TIbartuXCXdNsn+sL+uXJc0w7EmOyfX6bAKYc95Nr4ANwu+DVdFNv91KvjMjvz3gM+QxvdkJeF1K93wR5H/KC++B8N6iyJFz2DYffHS98999Td+bfEwrPfzX8exme0kb3CfA+MTd8vdydW56DufDh5Tx+fUCNOx+Mh+9tfSiO9T61lqp9+J2j1vs+At1wtZDJ6/Ft4C6b4pft8qlsiyCM8cINUz9D2PWXcQ/q2ht303cp+JRMx3hlykB0Xd+FcTdd+9v/jEqneCf9EpVO5XLSL1PpKZX+WdGO05SPyyvUesJBqNvCCpGOsLZNKU6sz7rjwNWsAwScqwO+GHdlqmmh36Yz0aby/b0DpzKsw3PIMsG5+0PME+gftT8kx5lz2Y6W/hWznu6jE7ybCD5GsAcW6OPZgv38QO8bcdcG2U02CMZJ5HXHyMlzWaaIph0nbwnqh36m90V2o37Ub50+eVvc2QOhdOzxxBk/+O3wT+O/A3XomY63fMZ7sA/ccUHv53yX8rWOC7e3smOyt6yNZctfZt4V3Jy1Y+7/w+6yPrqFfTfPOz3n33sB+/f2fbrYMJVH0I3TmZ2h/mxSzt3r8thxx0g7Dm/yLlF23PIQO24l7DizRkog478nxrw1XjevEG3hMyzNC12ZqIRP6YVqz+seyNAPlS13/3zqy6Pq64nej5D/x8gv9QbBoH+58vFT5PmZWnvR9t8P4sK3e5Lb9l5j/4X4Qf4JxU/SthzwlMGWC8LlIbbcdMgLr0W4ttx9Zj2Ky2MNugzRXgifJD+X61IF3rKeIvoGzhHZs7CI0/7ssQYzlEkmyPhz3tzMDHVyduFzpa/bXW8a7OmqjkbjfpG9wL6aruyrtJET6cMF52Vm27gB/wwraMwL8euyIMSvSySPX5d4iF+Xg4iH9ztzlOUrlVm2cnS/LgXyoG/8Ss3Bfx1nGfWwB/sbMZ7er8bTB9i20f6BiF/aRxDbNg9C7lscnwz8TuxDsDX+IGg/pMbPR8QaDGBh97hh6gtO+F4V/oEKZxX++zidy0Z8ub4cfEPZtB30t7ibru2gJ1U6ldNJf0ql36vS/6nSf6DSn1Hp2iZ4TqXfp/K/INIXhvjneRFt2Cx8HJDehm0DfQuZCbOL98ShIxlGwcE/nWxn0MWbVZBB14ZboGz3Pzi2WbjPlPHVbl2nKF6VqHT9nvH+QTrqonldWi3GlnMlb2CDqfIcCPgfAx58wlmFcFvjzdWY7+CMCf2oD4o+qeY7ZdUoB+CnhOxZTalmW/GpAAa/KcqfXTnK/DOUWdp8V3quv4Q0hVEn1IXtPm7LEu9QzVfVxw7jdMvHV1Qfe6tK1+fv307pc+X5YNg57I8fNo0=
*/