float randomnum(int &seed){
    seed = (seed * 2781 + 6351) % 4275;
    float caspita = seed / 4275.0;
    return caspita;
}

bool chance(float probability, int &seed){
    return randomnum(seed) < probability;
}

int interval(int min, int max, int &seed){
    return (int(randomnum(seed)*100000) % (max - min)) + min;
}
float intervalf(float min, float max, int &seed){
    return (randomnum(seed) * 100000 / 100000.0) * (max - min) + min;
}
