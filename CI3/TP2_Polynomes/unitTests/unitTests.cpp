#include <gtest/gtest.h>
#include "Polynome.h"

TEST(Creation, AvecCoefsNonNuls) {
    Polynome  p1{{1.2, 2, 3, 4} };
    Polynome  p2{{{0, 1.2}, {1, 2}, {2, 3}, {3, 4}} };
    EXPECT_EQ(p1, p2);
}

TEST(Creation, AvecCoefsNuls) {
    Polynome  p1{{{0, 1}, {1, 0}, {2, 3}, {3, 4}, {2000, 0}} };
    Polynome  p2{{{0, 1}, {2, 3}, {3, 4},         } };
    EXPECT_EQ(p1, p2);
}

TEST(Somme, Somme1) {
    Polynome  p1{{1, 0, 2, 1} };
    Polynome  p2{{1, 2, 0, 1} };
    Polynome  somme_ref{{2, 2, 2, 2} };
    EXPECT_EQ(p1 + p2, somme_ref);
    EXPECT_EQ(p2 + p1, somme_ref);
}

TEST(Somme, Somme2) {
    Polynome p1{{1, 0, 2, 1} };
    Polynome p2{{1, 2, 0, -1} };
    Polynome somme_ref{{2, 2, 2} };
    EXPECT_EQ(p1 + p2, somme_ref);
    EXPECT_EQ(p2 + p1, somme_ref);
}

TEST(Somme, Somme3) {
    Polynome p{{1, 0, 2, 1} };
    Polynome p_nul;
    EXPECT_EQ(p + p_nul, p);
    EXPECT_EQ(p_nul + p, p);
}

TEST(Somme, SommeAvecConstante) {
    Polynome p{{0, 0, 2, 1} };
    double d{ 1.2 };
    Polynome somme_ref{{1.2, 0, 2, 1} };
    EXPECT_EQ(p + d, somme_ref);
    EXPECT_EQ(d + p, somme_ref);
}

TEST(Derivation, initialiseAvecVector) {
    Polynome p{{1, 2, 3, 4} };
    Polynome deriv_ref{{2, 6, 12 } };
    EXPECT_EQ(p.derive(), deriv_ref);
}

TEST(Derivation, initialiseAvecMap) {
    Polynome p{{{0, 1}, {1, 2}, {2000, 3}} };
    Polynome deriv_ref{{{0, 2}, {1999, 6000}} };
    EXPECT_EQ(p.derive(), deriv_ref);
}

TEST(Derivation, ul) {
    Polynome p_nul;
    EXPECT_EQ(p_nul.derive(), p_nul);
}

TEST(Degre, degre1) {
    Polynome p{{1, 2, 1} };
    EXPECT_EQ(p.degree(), 2);
}

TEST(Degre, degre2) {
    Polynome p{{{0, 1}, {2000, 2} } };
    EXPECT_EQ(p.degree(), 2000);
}

TEST(Degre, degre3) {
    Polynome p{{1, 2, 3, 4, 0} };
    EXPECT_EQ(p.degree(), 3);
}

TEST(Degre, degre4) {
    Polynome p{{{0, 1}, {1, 2}, {2, 3}, {3, 4}, {2000, 0}} };
    EXPECT_EQ(p.degree(), 3);
}

TEST(Degre, degre5) {
    Polynome p1{{1, 0, 2, 1} };
    Polynome p2{{1, 2, 0, -1} };
    EXPECT_EQ((p1+p2).degree(), 2);
}

TEST(Degre, degre6) {
    Polynome p;
    EXPECT_EQ(p.degree(), -1);
}

TEST(Degre, degre7) {
    Polynome p({0 });
    EXPECT_EQ(p.degree(), -1);
}