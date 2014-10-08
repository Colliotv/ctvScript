#ifndef Status_h__
# define Status_h__

namespace cTVScript {
  typedef enum{
    CLEAR,
    ALREADY_EXIST,
    OBJECT_TYPE_IS_NOTLOADABLE,
    RETURN_ISREFERENCE,
    PARAMETER_IS_NULL
  } loading_status;
};

#endif
