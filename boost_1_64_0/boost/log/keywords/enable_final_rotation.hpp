/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/enable_final_rotation.hpp
 * \author Andrey Semashev
 * \date   27.11.2016
 *
 * The header contains the \c enable_final_rotation keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ENABLE_FINAL_ROTATION_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ENABLE_FINAL_ROTATION_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for enabling/disabling final log file rotation on sink backend destruction
BOOST_PARAMETER_KEYWORD(tag, enable_final_rotation)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ENABLE_FINAL_ROTATION_HPP_INCLUDED_

/* enable_final_rotation.hpp
vjp+tB8cAnM03KHwIh3HeSkcARfDkXCZjmtdqeOHf6Djh3+k44bv0vHB9+n44IfhJJ2vOBnu1nHBh3Rc8B/gVPgRvFzjP03Hbc+AGXAmbKfjeTPhbNgNzoFZMB9O0PG/l+v43xId5/t9WAxvh1fCDXAZ3AqXw0dhCayEK+AeeA18HV4P34aldjzhDfDPcCX8Cq6CseTvTTAJroad4BrYFa6FA+DtMBdugJNhOZwNN8K58E44X/dL4D3wu/BheCu8Dz4CH4BPwi3wGbgV/hw+CPeKvs4L8vies+W9gZT/AGS/ln8znVfWBraFbXVeenvYHWbCcbADzNX5CRfBTjpfqwtcCnvC1bA3XAPPgRthX7gZZsPn4ED4AjxX56MOgr+FQ+DbMAe+C4fCP8Nh8BM4Ejb0UM9gMzha53ONgSPgODgGTobz4cVwJbwEroaX6zyu6TqvNA++o/u/1/0jcLbO5yqADaOoR7ApnA/TYSE8Cy6A/WERPBcu1Hmmi+AUWAyXwqXwh3AZvB2WwLvhtXArLIU74I3wabgS/gKugm/Cm+FBuBq+C7vCr2A36InG3T8vVJ9JJC2Uc+C80Cd1/PgO2FznJfXVeUfZ8LCOG/+pzjt6UednVMJ8PT5f5yV8pfMQWnKet7Udvgs7w9/DbPgezIF/gBPh+5BnS8LR+Jp7TzkWEt8/o5cIP9L4/g2eDY9p//cp7KfzowfAxnY56Pzo4fAr7Q+/gZdAD8evgTHwXhgH98IG8Nfq/zcwUedFN4JV6m7GDz/rHz9c4Rz3rf3vtfUiHz/sGzuci5QgjI87M3Y4grHD/wtjhmsZKxzROOF/1Rhhxq1HPE64hjHC/1Pjg//ZY4NPd1zwf2JMsHM8MHMV/ivGBJ/KeOAcJDOJcbZIKbId2YscSTozvvbM78zvzO/M78zvzO/M78zvzO/M78zvzO/M78zvv/n3bxr/X1Q4W4b/n/b4//R2hKFjMqd49BugpiUZuYbv69UbzVjz4Sxur8MBvOtExJuxmLPcxgHgN3CtztYyFrb2NSYbOceKETbf8U0892g8G6uHRshV6CVtco0na0VYzvMzfrf29X+dY1Vzos16x/zwi3TmQ0OW+/mKlxQyDF/HTer6+jWNMdNwPI68LHEdJ6F6uJmx+YvyOav7+DKjL3G4MR19WVvfddw8uqHl9OO02svJNw6DNOp4Fl1325RdSdD4YxNnM5aFuOEucQvI96M6kIZP7MamUBfyPW9TwNwHlxXsrLBrERaI35FWX/4PCjMfJc+Rz12zcSBunIJg+Kat4dwnOnn4j7aasnU5ErSOqBmT+4bodrc6Erq9XuaIaOpUDHkra4F+J2Tcuk8nH502tk69y4zOJ6rTTnU2oZOBToInNjXxrLTYhOh2CWNjExJjo9zXSvSNW2qr7cDm3DqsyxmyRqKWVXmsV3mrltUWpKfdRu4OKCvX1etQDVtefcX/aC2vBu7t525/Pc/S8lpStNSUVcndut48ZdWYrUuR4DVdzfhpdJ1lVR1DudTjm5iU1XVuZSU6SaS/vZTVdLeyEp3R6GS6lVW9msuqg5QVPM2y6qdltV89HEZikQ+Qn6Br3RNYVnaldyubljqur57o/97qz/9JyLPua3sSruv6qWbuyTw5XmKNRcOl38N/7e1xuOjcLe2xCWddbDV0rvlryneGN43Whbi4tdcmsER0RhJOuteNvTJxm0R8RsqY8U1kXHqctD1ZT7yeXaQpFGl70/zc1ypVv7lxuhZw1GWJ9WJYxjsxqguLf7uvsat+luEnTuphcch6wL61YgspmI4yXvv01vj2rxWrY1e17hxoYMmvowbUAelHmWTcG1h3aIDB9ca1buA=
*/