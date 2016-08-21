#[macro_use]
extern crate qmlrs;
mod math;

fn main() {
    let mut engine = qmlrs::Engine::new();
    engine.create_view("examples/sailfishos_factorial.qml");
    engine.set_property("factorial", math::Factorial);
    engine.exec();
}
