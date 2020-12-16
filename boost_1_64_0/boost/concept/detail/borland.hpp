// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_DETAIL_BORLAND_DWA2006429_HPP
# define BOOST_CONCEPT_DETAIL_BORLAND_DWA2006429_HPP

# include <boost/preprocessor/cat.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>

namespace boost { namespace concepts {

template <class ModelFnPtr>
struct require;

template <class Model>
struct require<void(*)(Model)>
{
    enum { instantiate = sizeof((((Model*)0)->~Model()), 3) };
};

#  define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )         \
  enum                                                  \
  {                                                     \
      BOOST_PP_CAT(boost_concept_check,__LINE__) =      \
      boost::concepts::require<ModelFnPtr>::instantiate  \
  }

}} // namespace boost::concept

#endif // BOOST_CONCEPT_DETAIL_BORLAND_DWA2006429_HPP

/* borland.hpp
YtBGHD9sYr6wiWKwhOa+2uUJpll7pRKQT8V13zhf3/TTuOtySqezSzgAPLRwQsgzxnmAMSzwoMaVtBLWmSu7Cso46WoMAsr7J32ci/gog0Kg3WMMQr1fAekPzo76Vb3Lexs0kKDzCrBVY99onMiYn3lIdxSM8UhIG0lZKB0/cfyLPou7htqD/bnag71cS3r7VQGrO0PPv9XgHtHeoNzbJW1p81itPhFzagwxtr6wL775MoAxANrhGe51XFbTm3WBc9XpTSYWz+3w/iHSbBHm/RVP696EwFaDdnaG80Wrb8ZJkQeuuOi99EreJaY8P2GZ46YyLjwGsdyX4SY5vihVq7Vy32PPbrgKB1tSg38dYaA3o34uP1bd7Ko9OMR6ev0YxcK2D7brav12WYKBo1Wk+ZspDQYZXD9sITRoIUjrX4HQyhSxvq5o0uCgaQJHQkVG3OKVRnH6LLwEoh/DK4/i4GTfxLygBrOiFrxmere/io0p7+eV7uvMtv+JURxmH33LXY1g8IBUm0TEPXe8Edcn+23XqMdV75Kw7xIcPWxFX+PXHMFgN8Bylg3DxqFa8Xzu1te2MXgkuaSfVXbU67pjZIwZ5YGq6KjXCtjG565DMHXGAeVtu66J1Ru5nd5hEsebYsAQIf/XtxKacSnEPE8nGDsriHvE9QluxWpDiItvQHE17QN97VNcffs4cON6nO2ncvtNbBx2KVKvZ7fZuOZ6xXsYN6U8ul5Rz/+6GdD13g71+4mYMzc3MCsUg3vK2wGDt11BlN75XlW7g4YNgnNHnG/AlRJjL/6WhFZrF9duRTDELv7t1oRG7OJvb0NocBUFadtvR2jEZsa3JzTIDc6drnUHk3bB6yZYj607UT48cB+dpyHPpRMb4+kbdX+wbfLgNQussydPErp9xQLr5fE7bRxer0DM+6YIhpzpYzyVXQRTaxNO3plijhv1NH0XQivtxa6KdleTdsGrAqjX7XenfBupi617NsbTN/2aOpTHviiB+1CuiSOXI1APr/YoBpSEPlgDTbMmgBh3LgT6OnfuTLsUAbZ5bob7gTfA/Sp96a1cGuL5xfmfUR8uRRy4CbxIwnckA9tiOQn4L+51kbkfZ1GYZCKI3Iud+8H7Jbhbf7DMT8mAWdatscT8RWHeV+4N6cdWJgbKbfgNuNwY7HPRzTKc31wW6OQmv/HGE+fQiDFsJxGIbehytVg8t8O5xOZaHK7q0T/ylloc7kmjnbhCPU6v5FEfp684goNOimVdvdIofaWhrPGV67F2WRevWo+zy8quVoOjZcW3XaO40bK++uoGTrdjlDNYzCHdjNmp2xnKmae4Efq/DDooU9MhHXyTgPSV5nTOUBzSi+q87ad0feXFvhvk+UXvx2McIbPP+yHL4tTxI16/vOoeUtWlF1XDlZaSRs9+NlX5PzSzpCsO6f6YQcfLtsbcgtDLmQXGJsMzncuYmHLrDml32zSk6XU30m54OYNm+XPfeXmDRi8YY95/SjGwogItDO/0bbbp9fGKxrfYOBqvCNefFq6cPw5mjoi52xUoBvZ3K41hm7IwNv3gFYd0yIPe10K9feJKJR3bNrnncWVKgxfPxuQZ07jbVQwc7LDpsuL77atadFCd6fvlagadriDoXv64gQMZUBikw/6nTVeJmfGrr2nQrRUIrhOvRTC19fLkaxNMbb3I61CMTb/WdSldNzfUybatlG41N8xLdj0bh80N52Xz12/E1N0yxbbx5xsafDruBJ5V3QhoTffrjZj7NxnB2V0Q7+T8eRtgN3LHX9v/m47gzeaFuE03H8GZzQPrZHE74EbnUOhz80vknCMJE+5E3GduAfPIw13ldQl9K6HvVpPHdVk=
*/