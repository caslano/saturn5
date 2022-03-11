#ifndef DATE_TIME_TZ_DB_BASE_HPP__
#define DATE_TIME_TZ_DB_BASE_HPP__

/* Copyright (c) 2003-2005 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. 
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <boost/tokenizer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/throw_exception.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/time_zone_names.hpp>
#include <boost/date_time/time_zone_base.hpp>
#include <boost/date_time/time_parsing.hpp>
#include <boost/algorithm/string.hpp>

namespace boost {
  namespace date_time {

    //! Exception thrown when tz database cannot locate requested data file
    class data_not_accessible : public std::logic_error
    {
     public:
       data_not_accessible() : 
         std::logic_error(std::string("Unable to locate or access the required datafile.")) 
       {}
       data_not_accessible(const std::string& filespec) : 
         std::logic_error(std::string("Unable to locate or access the required datafile. Filespec: " + filespec)) 
       {}
    };
    
    //! Exception thrown when tz database locates incorrect field structure in data file
    class bad_field_count : public std::out_of_range
    {
     public:
       bad_field_count(const std::string& s) : 
         std::out_of_range(s) 
      {}
    };

    //! Creates a database of time_zones from csv datafile
    /*! The csv file containing the zone_specs used by the
     * tz_db_base is intended to be customized by the
     * library user. When customizing this file (or creating your own) the
     * file must follow a specific format.
     * 
     * This first line is expected to contain column headings and is therefore
     * not processed by the tz_db_base.
     *
     * Each record (line) must have eleven fields. Some of those fields can
     * be empty. Every field (even empty ones) must be enclosed in 
     * double-quotes.
     * Ex:
     * @code
     * "America/Phoenix" <- string enclosed in quotes
     * ""                <- empty field
     * @endcode
     * 
     * Some fields represent a length of time. The format of these fields 
     * must be:
     * @code
     * "{+|-}hh:mm[:ss]" <- length-of-time format
     * @endcode
     * Where the plus or minus is mandatory and the seconds are optional.
     * 
     * Since some time zones do not use daylight savings it is not always 
     * necessary for every field in a zone_spec to contain a value. All 
     * zone_specs must have at least ID and GMT offset. Zones that use 
     * daylight savings must have all fields filled except: 
     * STD ABBR, STD NAME, DST NAME. You should take note 
     * that DST ABBR is mandatory for zones that use daylight savings 
     * (see field descriptions for further details).
     *
     * ******* Fields and their description/details ********* 
     *     
     * ID: 
     * Contains the identifying string for the zone_spec. Any string will
     * do as long as it's unique. No two ID's can be the same. 
     *
     * STD ABBR:
     * STD NAME:
     * DST ABBR:
     * DST NAME:
     * These four are all the names and abbreviations used by the time 
     * zone being described. While any string will do in these fields, 
     * care should be taken. These fields hold the strings that will be 
     * used in the output of many of the local_time classes. 
     * Ex:
     * @code
     * time_zone nyc = tz_db.time_zone_from_region("America/New_York");
     * local_time ny_time(date(2004, Aug, 30), IS_DST, nyc);
     * cout << ny_time.to_long_string() << endl;
     * // 2004-Aug-30 00:00:00 Eastern Daylight Time
     * cout << ny_time.to_short_string() << endl;
     * // 2004-Aug-30 00:00:00 EDT
     * @endcode
     *
     * NOTE: The exact format/function names may vary - see local_time 
     * documentation for further details.
     *
     * GMT offset:
     * This is the number of hours added to utc to get the local time 
     * before any daylight savings adjustments are made. Some examples 
     * are: America/New_York offset -5 hours, & Africa/Cairo offset +2 hours.
     * The format must follow the length-of-time format described above.
     *
     * DST adjustment:
     * The amount of time added to gmt_offset when daylight savings is in 
     * effect. The format must follow the length-of-time format described
     * above.
     *
     * DST Start Date rule:
     * This is a specially formatted string that describes the day of year
     * in which the transition take place. It holds three fields of it's own,
     * separated by semicolons. 
     * The first field indicates the "nth" weekday of the month. The possible 
     * values are: 1 (first), 2 (second), 3 (third), 4 (fourth), 5 (fifth), 
     * and -1 (last).
     * The second field indicates the day-of-week from 0-6 (Sun=0).
     * The third field indicates the month from 1-12 (Jan=1).
     * 
     * Examples are: "-1;5;9"="Last Friday of September", 
     * "2;1;3"="Second Monday of March"
     *
     * Start time:
     * Start time is the number of hours past midnight, on the day of the
     * start transition, the transition takes place. More simply put, the 
     * time of day the transition is made (in 24 hours format). The format
     * must follow the length-of-time format described above with the 
     * exception that it must always be positive.
     *
     * DST End date rule:
     * See DST Start date rule. The difference here is this is the day 
     * daylight savings ends (transition to STD).
     *
     * End time:
     * Same as Start time.
     */
    template<class time_zone_type, class rule_type>
    class tz_db_base {
    public:
      /* Having CharT as a template parameter created problems 
       * with posix_time::duration_from_string. Templatizing 
       * duration_from_string was not possible at this time, however, 
       * it should be possible in the future (when poor compilers get 
       * fixed or stop being used). 
       * Since this class was designed to use CharT as a parameter it 
       * is simply typedef'd here to ease converting in back to a 
       * parameter the future */
      typedef char char_type;

      typedef typename time_zone_type::base_type time_zone_base_type;
      typedef typename time_zone_type::time_duration_type time_duration_type;
      typedef time_zone_names_base<char_type> time_zone_names;
      typedef boost::date_time::dst_adjustment_offsets<time_duration_type> dst_adjustment_offsets;
      typedef std::basic_string<char_type> string_type;

      //! Constructs an empty database
      tz_db_base() {}

      //! Process csv data file, may throw exceptions
      /*! May throw bad_field_count exceptions */
      void load_from_stream(std::istream &in)
      {
        std::string buff;
        while( std::getline(in, buff)) {
          boost::trim_right(buff);
          parse_string(buff);
        }
      }

      //! Process csv data file, may throw exceptions
      /*! May throw data_not_accessible, or bad_field_count exceptions */
      void load_from_file(const std::string& pathspec)
      {
        std::string  buff;
        
        std::ifstream ifs(pathspec.c_str());
        if(!ifs){
          boost::throw_exception(data_not_accessible(pathspec));
        }
        std::getline(ifs, buff); // first line is column headings
        this->load_from_stream(ifs);
      }

      //! returns true if record successfully added to map
      /*! Takes a region name in the form of "America/Phoenix", and a 
       * time_zone object for that region. The id string must be a unique 
       * name that does not already exist in the database. */
      bool add_record(const string_type& region, 
                      boost::shared_ptr<time_zone_base_type> tz)
      {
        typename map_type::value_type p(region, tz); 
        return (m_zone_map.insert(p)).second;
      }

      //! Returns a time_zone object built from the specs for the given region
      /*! Returns a time_zone object built from the specs for the given 
       * region. If region does not exist a local_time::record_not_found 
       * exception will be thrown */
      boost::shared_ptr<time_zone_base_type> 
      time_zone_from_region(const string_type& region) const 
      {
        // get the record
        typename map_type::const_iterator record = m_zone_map.find(region);
        if(record == m_zone_map.end()){
          return boost::shared_ptr<time_zone_base_type>(); //null pointer
        }
        return record->second;
      }

      //! Returns a vector of strings holding the time zone regions in the database
      std::vector<std::string> region_list() const
      {
        typedef std::vector<std::string> vector_type;
        vector_type regions;
        typename map_type::const_iterator itr = m_zone_map.begin();
        while(itr != m_zone_map.end()) {
          regions.push_back(itr->first);
          ++itr;
        }
        return regions;
      }
    
    private:
      typedef std::map<string_type, boost::shared_ptr<time_zone_base_type> > map_type;
      map_type m_zone_map;

      // start and end rule are of the same type
      typedef typename rule_type::start_rule::week_num week_num;

      /* TODO: mechanisms need to be put in place to handle different
       * types of rule specs. parse_rules() only handles nth_kday
       * rule types. */
      
      //! parses rule specs for transition day rules
      rule_type* parse_rules(const string_type& sr, const string_type& er) const
      {
        // start and end rule are of the same type, 
        // both are included here for readability
        typedef typename rule_type::start_rule start_rule;
        typedef typename rule_type::end_rule end_rule;
       
        // these are: [start|end] nth, day, month
        int s_nth = 0, s_d = 0, s_m = 0;
        int e_nth = 0, e_d = 0, e_m = 0;
        split_rule_spec(s_nth, s_d, s_m, sr);
        split_rule_spec(e_nth, e_d, e_m, er);
        
        typename start_rule::week_num s_wn, e_wn;
        s_wn = get_week_num(s_nth);
        e_wn = get_week_num(e_nth);
        
        
        return new rule_type(start_rule(s_wn,
                                        static_cast<unsigned short>(s_d),
                                        static_cast<unsigned short>(s_m)),
                             end_rule(e_wn,
                                      static_cast<unsigned short>(e_d),
                                      static_cast<unsigned short>(e_m)));
      }
      //! helper function for parse_rules()
      week_num get_week_num(int nth) const
      {
        typedef typename rule_type::start_rule start_rule;
        switch(nth){
        case 1:
          return start_rule::first;
        case 2:
          return start_rule::second;
        case 3:
          return start_rule::third;
        case 4:
          return start_rule::fourth;
        case 5:
        case -1:
          return start_rule::fifth;
        default:
          // shouldn't get here - add error handling later
          break;
        }
        return start_rule::fifth; // silence warnings
      }
          
      //! splits the [start|end]_date_rule string into 3 ints
      void split_rule_spec(int& nth, int& d, int& m, string_type rule) const
      {
        typedef boost::char_separator<char_type, std::char_traits<char_type> > char_separator_type;
        typedef boost::tokenizer<char_separator_type,
                                 std::basic_string<char_type>::const_iterator,
                                 std::basic_string<char_type> > tokenizer;
        typedef boost::tokenizer<char_separator_type,
                                 std::basic_string<char_type>::const_iterator,
                                 std::basic_string<char_type> >::iterator tokenizer_iterator;
        
        const char_type sep_char[] = { ';', '\0'};
        char_separator_type sep(sep_char);
        tokenizer tokens(rule, sep); // 3 fields

        if ( std::distance ( tokens.begin(), tokens.end ()) != 3 ) {
          std::ostringstream msg;
          msg << "Expecting 3 fields, got " 
              << std::distance ( tokens.begin(), tokens.end ()) 
              << " fields in line: " << rule;
          boost::throw_exception(bad_field_count(msg.str()));
        }

        tokenizer_iterator tok_iter = tokens.begin(); 
        nth = std::atoi(tok_iter->c_str()); ++tok_iter;
        d   = std::atoi(tok_iter->c_str()); ++tok_iter;
        m   = std::atoi(tok_iter->c_str());
      }

     
      //! Take a line from the csv, turn it into a time_zone_type.
      /*! Take a line from the csv, turn it into a time_zone_type,
       * and add it to the map. Zone_specs in csv file are expected to 
       * have eleven fields that describe the time zone. Returns true if 
       * zone_spec successfully added to database */
      bool parse_string(string_type& s)
      {
        std::vector<string_type> result;
        typedef boost::token_iterator_generator<boost::escaped_list_separator<char_type>, string_type::const_iterator, string_type >::type token_iter_type;

        token_iter_type i = boost::make_token_iterator<string_type>(s.begin(), s.end(),boost::escaped_list_separator<char_type>());

        token_iter_type end;
        while (i != end) {
          result.push_back(*i);
          i++;
        }

        enum db_fields { ID, STDABBR, STDNAME, DSTABBR, DSTNAME, GMTOFFSET,
                         DSTADJUST, START_DATE_RULE, START_TIME, END_DATE_RULE,
                         END_TIME, FIELD_COUNT };

        //take a shot at fixing gcc 4.x error
        const unsigned int expected_fields = static_cast<unsigned int>(FIELD_COUNT);
        if (result.size() != expected_fields) { 
          std::ostringstream msg;
          msg << "Expecting " << FIELD_COUNT << " fields, got " 
            << result.size() << " fields in line: " << s;
          boost::throw_exception(bad_field_count(msg.str()));
          BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(return false); // should never reach
        }

        // initializations
        bool has_dst = true; 
        if(result[DSTABBR] == std::string()){
          has_dst = false;
        }


        // start building components of a time_zone
        time_zone_names names(result[STDNAME], result[STDABBR],
                              result[DSTNAME], result[DSTABBR]);

        time_duration_type utc_offset = 
          str_from_delimited_time_duration<time_duration_type,char_type>(result[GMTOFFSET]);
        
        dst_adjustment_offsets adjust(time_duration_type(0,0,0),
                                      time_duration_type(0,0,0),
                                      time_duration_type(0,0,0));

        boost::shared_ptr<rule_type> rules;

        if(has_dst){
          adjust = dst_adjustment_offsets(
                                          str_from_delimited_time_duration<time_duration_type,char_type>(result[DSTADJUST]),
                                          str_from_delimited_time_duration<time_duration_type,char_type>(result[START_TIME]),
                                          str_from_delimited_time_duration<time_duration_type,char_type>(result[END_TIME])
                                          );

          rules = 
            boost::shared_ptr<rule_type>(parse_rules(result[START_DATE_RULE],
                                                     result[END_DATE_RULE]));
        }
        string_type id(result[ID]);
        boost::shared_ptr<time_zone_base_type> zone(new time_zone_type(names, utc_offset, adjust, rules));
        return (add_record(id, zone));
        
      } 
     
    };

} } // namespace

#endif // DATE_TIME_TZ_DB_BASE_HPP__

/* tz_db_base.hpp
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
*/