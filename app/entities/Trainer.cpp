#include "Trainer.hpp"

Trainer::Trainer()
    : name(""), type(TrainerType::WILD), level(5), city("")
{
}

Trainer::Trainer(const std::string &n, TrainerType t, int lvl, const std::string &c)
    : name(n), type(t), level(lvl), city(c)
{
}
