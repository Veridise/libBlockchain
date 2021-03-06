pragma solidity ^0.8.9;

// example.sol
contract example {
        // Process state
        enum State {
                Running,
                Sleeping,
                Waiting,
                Stopped,
                Zombie,
                StateCount
        }

        // Variables in contract storage
        State state;
        int32 public pid;
        uint32 reaped = 3;
        mapping (address => uint) aMap;
        address[] anArray;

        function getAMap(mapping(address => uint) storage m) internal view returns (bool) {
            return m[address(0)] == 0;
        }

        function getArray(address[] calldata a) public pure returns (bool) {
            return a[0] == address(0);
        }

        function getState() public view returns (State) {
            return state;
        }

        function setPid(int32 p) public {
            pid = p;
        }

        function getPid() public view returns (int32) {
            return pid;
        }

        function getReaped() public view returns (uint32) {
            return reaped;
        }

        // Constants
        State constant bad_state = State.Zombie;
        int32 constant first_pid = 1;

        // Our constructors
        constructor(int32 _pid) {
                // Set contract storage
                setPid(_pid);
        }

        // Reading but not writing contract storage means function
        // can be declared view
        function is_zombie_reaper() public view returns (bool) {
                /* must be pid 1 and not zombie ourselves */
                return (pid == first_pid && getState() != State.Zombie);
        }

        // Returning a constant does not access storage at all, so
        // function can be declared pure
        function systemd_pid() public pure returns (uint32) {
                // Note that cast is required to change sign from
                // int32 to uint32
                return uint32(first_pid);
        }

        /// Convert celcius to fahrenheit
        function celcius2fahrenheit(int32 celcius) pure public returns (int32) {
                int32 fahrenheit = celcius * 9 / 5 + 32;

                return fahrenheit;
        }

        function v_mul(int32 a, int32 b) pure public returns (int32) {
            return int32(a * b);
        }

        function v_div(int32 a, int32 b) pure public returns (int32) {
            return int32(a / b);
        }

        function v_add(int32 a, int32 b) pure public returns (int32) {
            return int32(a + b);
        }

        function celcius2fahrenheit1(int32 celcius) pure public returns (int32) {
                int32 fahrenheit = v_add(v_div(v_mul(celcius, 9), 5), 32);

                return fahrenheit;
        }

        /// Convert fahrenheit to celcius
        function fahrenheit2celcius(int32 fahrenheit) pure public returns (int32) {
                return (fahrenheit - 32) * 5 / 9;
        }

        /// is this number a power-of-two
        function is_power_of_2(uint n) pure public returns (bool) {
                return n != 0 && (n & (n - 1)) == 0;
        }

        /// calculate the population count (number of set bits) using Brian Kerningham's way
        function population_count(uint n) pure public returns (uint count) {
                for (count = 0; n != 0; count++) {
                        n &= (n - 1);
                }
        }

        /// calculate the power of base to exp
        function power(uint base, uint exp) pure public returns (uint) {
                return base ** exp;
        }

        /// returns true if the address is 0
        function is_address_zero(address a) pure public returns (bool) {
                return a == address(0);
        }

        /// reverse the bytes in an array of 8 (endian swap)
        function byte8reverse(bytes8 input) public pure returns (bytes8 out) {
                out = ((input << 56) & hex"ff00_0000_0000_0000") |
                          ((input << 40) & hex"00ff_0000_0000_0000") |
                          ((input << 24) & hex"0000_ff00_0000_0000") |
                          ((input <<  8) & hex"0000_00ff_0000_0000") |
                          ((input >>  8) & hex"0000_0000_ff00_0000") |
                          ((input >> 24) & hex"0000_0000_00ff_0000") |
                          ((input >> 40) & hex"0000_0000_0000_ff00") |
                          ((input >> 56) & hex"0000_0000_0000_00ff");
        }

        /// This mocks a pid state
        function get_pid_state(uint64 _pid) pure private returns (State) {
                uint64 n = 8;
                for (uint16 i = 1; i < 10; ++i) {
                        if ((i % 3) == 0) {
                                n *= _pid / uint64(i);
                        } else {
                                n /= 3;
                        }
                }

                return State(n % uint64(State.StateCount));
        }

        /// Overloaded function with different return value!
        function get_pid_state() view private returns (uint32) {
                return getReaped();
        }

        function reap_processes() public {
                uint32 n = 0;

                while (n < 100) {
                        if (get_pid_state(n) == State.Zombie) {
                                // reap!
                                reaped += 1;
                        }
                        n++;
                }
        }

        function run_queue() public pure returns (uint16) {
                uint16 count = 0;
                // no initializer means its 0.
                uint32 n=0;

                do {
                        if (get_pid_state(n) == State.Waiting) {
                                count++;
                        }
                }
                while (++n < 1000);

                return count;
        }

        // cards
        enum suit { club, diamonds, hearts, spades }
        enum value { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace }
        struct card {
                value v;
                suit s;
        }

        function getCardV(card memory c) public pure returns (value) {
            return c.v;
        }

        function getCardS(card memory c) public pure returns (suit) {
            return c.s;
        }

        card card1 = card(value.two, suit.club);
        card card2 = card({s: suit.club, v: value.two});

        function getCard1() public view returns (card memory) {
            return card1;
        }
        function getCard2() public view returns (card memory) {
            return card2;
        }

        function setCard1(card memory c) public {
            card1 = c;
        }

        function createCard(value val, suit st) public pure returns (card  memory) {
            return card({s: st, v: val});
        }

        // This function does a lot of copying
        function set_card1(card memory c) public returns (card memory previous) {
                previous = getCard1();
                setCard1(c);
        }

        /// return the ace of spades
        function ace_of_spades() public pure returns (card memory) {
                return createCard(value.ace, suit.spades);
                //return card({s: suit.spades, v: value.ace });
        }

        /// score card
        function score_card(card memory c) public pure returns (uint32 score) {
                if (getCardS(c) == suit.hearts) {
                        if (getCardV(c) == value.ace) {
                                score = 14;
                        }
                        if (getCardV(c) == value.king) {
                                score = 13;
                        }
                        if (getCardV(c) == value.queen) {
                                score = 12;
                        }
                        if (getCardV(c) == value.jack) {
                                score = 11;
                        }
                }
                // all others score 0
        }
}
