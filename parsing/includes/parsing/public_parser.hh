#ifndef Public_parser_h__
# define Public_parser_h__

class public_parser{
public:
  struct context_saver {
    size_t save;
  };
  const context_saver& createContextSaver();
  
  virtual bool stackOperand() = 0;

};

#endif
