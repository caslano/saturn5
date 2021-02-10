
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined(BOOST_WINDOWS)
# include <boost/context/windows/protected_fixedsize_stack.hpp>
#else
# include <boost/context/posix/protected_fixedsize_stack.hpp>
#endif

/* protected_fixedsize_stack.hpp
PherVSKdwrFy9lSQLHFtVf5QJqMSI+2sqDFZWJ9gnPyMShwK6FWvP+vsBb38SjROH0FPVDY4yOivIKNj1rDMD/KA9zI3LtF+RDQExHnn/HUQ+Gxd/EiEH3T8HvOAjLDtbZXMgA6AWApEt5WnVgFxkqtZlUJ6dDTL2/a9fyEEUWuZt30kGHVlFlslJ7AnL5DR0Ztj9g8JHd0Mh3zFdECraAYEho4fz9pVi8BW3itbg5wbCQwSfw23nBw+d2DemhVEzVI1QTMtwOfbgFC/JoQB/1thGXclI3+N05DOPaMxFFjsUNJmBpjorvvdy/40BI+pygp9FYDbnU4S7rXUHPwSjcHhKRinyzD4NpZOMtfw0NbWc2SgUY4ccZgcjr1tIthvLuXFZ8cgycCFV1HOOLHlgJcsAaJgkkj5bHrqC/Ugk0IdswqVWOXfFak1vnINeEBxqmi5Fw3T7OQ6Nbmn5Zl/ZmnrF86yj2LyKXtK7ASSTv0rZsq1cs7DVTyrQ00OPgkd+ooNeaB88cweeC7Q/I6bwt4jMGbJJ/o58ar2duip9iIEa0t8em5tzpSaMHjNYp7yvGqExnjBmCgBFlg7jNCGdMAtFrQwBAte9aopCZXl5IwFlsaqwoARGMCXodiyzuXeKe6FwNfLkn93ICDY
*/