#include <print>

struct Context;

struct State {
  virtual void handle(Context &ctx) = 0;
  virtual ~State() = default;
};

struct ConcreteStateA;
struct ConcreteStateB;

struct Context {
  State *state;

  Context(State *initial) : state(initial) {}

  void setState(State *newState) {
    delete state;
    state = newState;
  }

  void request() { state->handle(*this); }

  ~Context() { delete state; }
};

struct ConcreteStateA : State {
  void handle(Context &ctx) override;
};

struct ConcreteStateB : State {
  void handle(Context &ctx) override {
    std::println("StateB handling request -> transitioning to StateA");
    ctx.setState(new ConcreteStateA());
  }
};

void ConcreteStateA::handle(Context &ctx) {
  std::println("StateA handling request -> transitioning to StateB");
  ctx.setState(new ConcreteStateB());
}

int main() {
  Context ctx(new ConcreteStateA());

  ctx.request(); // StateA -> StateB
  ctx.request(); // StateB -> StateA
  ctx.request(); // StateA -> StateB

  return 0;
}
