#ifndef Key_h__
# define Key_h__

namespace cTVScript {

  class Key{
  private:
    std::vector<Loadable*> changed;
  public:
    static std::shared_ptr<Key> create() { return std::shared_ptr<Key> (new Key()); }
    void	notify(const Loadable*) {}

  public:
    ~Key() {
      for (auto loadable: changed)
	Surveyor::get()->update(loadable);
    } // on destruct avert Surveyor
  private:
    Key() {}
  };
  typedef std::shared_ptr<Key> DestructibleKey;

};

#endif
