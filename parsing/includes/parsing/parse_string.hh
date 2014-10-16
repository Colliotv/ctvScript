#ifndef Parse_string_h__
# define Parse_string_h__

namespace cTVScript {
  namespace parsing {

    /*
     * interface that sould be herited by all parsing class
     */
    class parsingImpl {
    public:
      virtual std::string parse_string(std::string scrypt_left) = 0;
    };
  };

};

#endif
