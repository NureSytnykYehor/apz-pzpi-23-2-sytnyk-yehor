#![allow(dead_code)]

trait State {}

struct Draft;
struct Published;
struct Unmoderated;
struct Deleted;

impl State for Draft {}
impl State for Published {}
impl State for Unmoderated {}
impl State for Deleted {}

struct Post<S: State> {
    state: S,
}

impl Post<Draft> {
    fn publish(self) -> Post<Published> {
        Post { state: Published }
    }
}

impl Post<Published> {}
impl Post<Unmoderated> {}
impl Post<Deleted> {}

fn main() {
    let post = Post { state: Draft };
    let _published = post.publish();
}
