# worm

An attempt in modeling the roundworm's nervous system


# TODO

- [x] bound energy between 0 and 9
- [x] introduce basal metabolism, with energy decreasing with number of neurons in the brain
- [x] introduce energy gain as function of 5 * exp (-0.1 * distanceToSource)
- [x] bound possible worm movements so it does not exit cave
- [x] make functions parametrable on the fly
- [ ] make the energy a float, to allow for more precision


# Neurons creation / deletion rules

Two types of neurons will be considered [1]:

1. sensory neurons
   Those propagate a stimulus from a receptor to the brain

2. motor neurons
   Those convey commands to muscles


## Sensory neurons

* neurons are only connected to a single source.
Physically, receptors are far apart, one looking on left side,
other looking on right side. This to avoid the complexity of having to turn worm's head.

* when the stimulus level perceived by the brain is too low, it tries
to create a new neuron. The receptor to which this neuron is attached is based
on the following algorithm:

  1. if the brain has some neurons on both sides, then it does not create
     any neurons, since it wouldn't bring higher stimulus levels
  2. if the brain has some neurons on only one side, then it creates the
     neuron on the other side, assuming it has enough energy
  3. if the brain does not have any neurons, it chooses the side randomly
     and creates the neuron, assuming it has enough energy

* when a neuron does not get enough stimulus for more than a fixed amount of time,
it is destroyed (brain considers it is useless).


## Motor neurons

* all motor neurons are connected to the brain

* when the brain perceives a sufficient level of stimulus from one side,
it tries to move to this side by activating the needed muscles, based on
the following algorithm:

  1. if the brain does not have any motor neuron connected to the side it
     wants to move to, then it creates one, assuming it has enough energy
  2. if the brain already has a neuron connected to the side it wants to
     move to, then it does not create any additional neuron

* when a motor neuron does not get triggered for more than a fixed amount
of time, then it is destroyed (brain considers it useless)


# Worm movement rules

* When worm perceives a sufficient level of stimulus from one side,
it tries to move in this direction by triggering its motor neuron linked
to the muscle on this side.

* When the energy the worm is able to absorb is sufficient, it stops
moving.


---

[1] https://www.khanacademy.org/science/biology/human-biology/neuron-nervous-system/a/overview-of-neuron-structure-and-function
