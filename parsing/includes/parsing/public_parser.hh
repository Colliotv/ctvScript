#ifndef Public_parser_h__
# define Public_parser_h__

namespace ctvscript {
  namespace parser{
    class public_parser{
    public:
      struct context_saver {
	size_t save;
      };
      const context_saver& createContextSaver();
    
      virtual bool			stackOperand() = 0;
      virtual bool			Call() = 0;
      virtual architecture::type::info* Type() = 0;
    };
  };
};
#endif
