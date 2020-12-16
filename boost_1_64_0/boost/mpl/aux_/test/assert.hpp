
#ifndef BOOST_MPL_AUX_TEST_ASSERT_HPP_INCLUDED
#define BOOST_MPL_AUX_TEST_ASSERT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/cat.hpp>

#define MPL_ASSERT(pred)                BOOST_MPL_ASSERT(pred)
#define MPL_ASSERT_NOT(pred)            BOOST_MPL_ASSERT_NOT(pred)
#define MPL_ASSERT_MSG(c, msg, types)   BOOST_MPL_ASSERT_MSG(c, msg, types)
#define MPL_ASSERT_RELATION(x, rel, y)  BOOST_MPL_ASSERT_RELATION(x, rel, y)

#define MPL_ASSERT_INSTANTIATION(x) \
    enum { BOOST_PP_CAT(instantiation_test, __LINE__) = sizeof( x ) } \
/**/

#endif // BOOST_MPL_AUX_TEST_ASSERT_HPP_INCLUDED

/* assert.hpp
+zOmhfhEz4fYQ3w2HIyP+VBS73bNelwym1di/yG2sz3DdtxxdRhpzmw73XJE/p/xXs5htrM7ejup2Zv1e8czm99lV9hOAyGvUDd9HrSD2xlkOyYeTL0/8vDvbYm9Dy76/sPBOUOfUkhjQ2FEpA59Er3tQYPdpt4zLalZz9MM99aEepW2it+uS5+FeEXPIZQkXit/jtdhl3Fm985bQ8Y5fXL9cp6JkZG69fN2D7vMfy0fCkXlgxkswppj6keuX9bDryqpn58ejJMcHNAroWGLZm07tfnNeB1pI/3fayO9dEpqvm3YmmNAnlGfDvyg6meNH7z3oX9NG2mVuHBtwTCONkN/5PbQj/kCc/NFhrbVcF3glUnbauHQtnoy43kKi7AoS7EYq7E4m7IEW7MkE1mKySzD4TyN43k6r2Y53szyXMYKXM1KfIyVuYlVuJ3VuJvV+SFrcT/PYj5xrs2CPIdleC7rsgEbsSEvZiN2YxMOZVNewWacyZa8nW25mB24iufzEXbiFl7CHezGV9idu5jIb5nE4+VxLxZgMotyICvxcjZlCltxKHtyOPtyBKdwFKdxNBfxCi7hWK7geD7CK/kyr+KrnMi3OYl7eDV/4DU8wGsPjg8L1yzhWmZzzPiwhaH+3M3jeQ/zczHP4BJW5r1sxaVsz2VR/eUbwvqPy6R+3hLWfyuP5W1Ry23/leWuD8vdEJabFrXc7rBc7kyWWxmWW8VjqM6F8UvhnM8GYbno8Uu3h/1hHitwPuvyzoPjqsJ5m40zeRbcA2G7D/I4PsRTuSbk48OsxUfYkGuj0rMyrPf4TNJzU1jvDObhzUwfJ789LNc3LBc9Tv7RsNxjLMwNrMbHQzw2sh2fYmc+zURuYjI3R8XPufCQ+b01bGdbyO9njzzj7j++TX/CvcY4CBuEXcJ+IX6pMQdCe2GwME1YuvSf0/b/L+j/792r2mW/u/8/MhfMZWc69jweOZ1e0OH8hME9RDm1TeCNqDaB0eGcuifsw28Lkeesn/fYwXnSm1a7LPLA/azMk3v4z3mO/PZO/XvUPL+pfx/86/N0HBPaE3qE30aXCqMj84tsyBjvlJRqAwf0G5Hl30ajIvOCMmYO3F+d62RdiMskobAwPOTh7oxx8VjqDHPWxr6uEg/lWyd1O4Xish1WfqbHeXfMuIo93s9xEpQRGfLvQPitPIfHcxbH1I7Ul9g4R/Iw6/Nl/HpcQ/7GtHeMHJkx7oltQ104xFwzse0yfWPGiCQenDMjvK8al2GOFZtLbV/ZkC2tzWC899dulG4WSp9LI8zPMqTfgP69Q3ln9tv8llD/ZoRnuZd4+hf5l5g8NCvzxOQ8caFls/L8/BExZT88vI8/WBd++/n5+aPG2AxP7i+GGX//bwi/s8eG9I0Sxknf7kzTF6kjWUtj601ZTOOImDQOD2kMdSizNEanqVdyUj+7W2y6M5Th0vD7+fmQxq2hDMdt+kUazR+SlTmhcp5YbXPW0veL4+E/UIbp+8hI+aHx7Od9JEfY36PKc2mYU//PYUx2L0bKc9rmzNIaKc+szPOe88QPt/z+9B6iPMM+HZXeqPIdEn0MiJ7L9RDnizzhcuDhHL7H+zm3svPFM79If3L/sL92PNTxLqQ95/P/WNoHpqc9dkxcTNqWxqR9d/h7z/D3XeF9el7uCe+Hhvcbo8bDRY53K9WBY+TDHY55LbZG4h4zZ13iwEznKNsQ/j7U3/NH5fmQMGlUdDmlz0O4LbwfGr4TffwdErazPbzvmZgWvzUycKMfAp/7/n3bfo7f/elzeYXj+M709+E4vzm8H+J9ZNtrUt+H9vmwjnXp36maVi/St5cjd9rvyWuf+3l7K9O/G9o=
*/