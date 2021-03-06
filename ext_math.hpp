#ifndef EXT_MATH_H_INCLUDED
  #define EXT_MATH_H_INCLUDED 1
  #include<iostream>
  #include<vector>
  #include<initializer_list>
  #define DEFAULT_ERR -1
  #define ERR(x) std::cerr << x;
  // Math
  namespace Math /// Version: 0.3
  {
    namespace proto_Vector /// Version: 0.1
    {
     	// 2D Vector
     	template<typename T>
     	struct Vector2
     	{
     	private:	 
	 		// Coordinates
     		T x;
     		T y;

	 		// The core of any Vector here -- std::vector
     		std::vector<T> Vec {x, y};

	 		// Vectors' properties
     		enum class DIR { HORIZON, VERTIC, CROSS, null } Direction;
     		enum SENSEOFVEC { UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT, null } VecSense;

     		//================================================================================================= 
     	public:

	 		Vector2() : x(0), y(0), Direction(DIR::null), VecSense(SENSEOFVEC::null) {}
	 		explicit Vector2(T x, T y, DIR Direction, SENSEOFVEC VecSense)
	 		{
	 		 	this->x = x;
				this->y = y;
				this->Direction = Direction;
			 	this->VecSense = VecSense;
	 		}
	 		explicit Vector2(T x, T y) { this->x = x; this->y = y; }
			explicit Vector2(const Vector2& other) { return this = other; }
			explicit Vector2(Vector2&& other) { return this = std::move(other); }
	 		// ---------------------------------------------------------------------------------------------
     		// Operators
	 		/// TODO: +=, -=, *=, /=, %=
			Vector2 operator=(const Vector2& other)
			{
				this->x = other.x;
				this->y = other.y;
				this->Direction = other.Direction;
				this->VecSense = other.VecSense;
				return *this;
			}
			Vector2 operator=(Vector2&& other) { return this = std::move(other); }
	 		T& operator[](size_t i)
	 		{
	 			return Vec[i];
	 		}
     		friend Vector2& operator-(Vector2& vec, Vector2& vec2) { return Vector2(vec.x - vec2.x, vec.y - vec2.y); }
     		friend Vector2& operator+(Vector2& vec, Vector2& vec2) { return Vector2(vec.x + vec2.x, vec.y + vec2.y); }
     		friend Vector2& operator*(Vector2& vec, Vector2& vec2) { return Vector2(vec.x * vec2.x, vec.y * vec2.y); }
     		friend Vector2& operator/(Vector2& vec, Vector2& vec2) { return Vector2(vec.x / vec2.x, vec.y / vec2.y); }

	 		friend bool operator>(Vector2& vec, Vector2& vec2) { return vec.x == vec2.x && vec.y == vec2.y && vec.Direction == vec2.Direction && vec.VecSense == vec2.VecSense; }
	 		friend bool operator<(Vector2& vec, Vector2& vec2) { return !(vec > vec2) && vec != vec2; }
	 		friend bool operator>=(Vector2& vec, Vector2& vec2) { return !(vec < vec2); }
	 		friend bool operator<=(Vector2& vec, Vector2& vec2) { return !(vec > vec2); }
     		friend bool operator==(Vector2& vec, Vector2& vec2)
     		{
     		   if((vec.x == vec2.x) && (vec.y == vec2.y) && (vec.DIR == vec2.DIR) && (vec.SENSEOFVECTOR == vec2.SENSEOFVECTOR))
     		       return true;
     		   else return false;
     		}
     		friend bool operator!=(Vector2& vec, Vector2& vec2)
     		{
     		    if(vec == vec2)
     		        return false;
     		    else return true;
     		}
	 		friend short operator<=>(Vector2& vec, Vector2& vec2)
	 		{
				if(vec == vec2) return 0;
				else if(vec > vec2) return 1;
				else return -1;
			}
			Vector2 operator""v2(std::initializer_list<T>& list) { return Vector2(list[0], list[1]);}
			Vector2 operator""v2(T& y) { return Vector2<T>(nullptr, y); } // Helper for operator ,(T, Vector2)
			Vector2 operator,(T& x, Vector2& y) { return Vector2(x, y.y);
	   };
    }
    namespace proto_pluralTheorem
    {
		template<typename T>
        struct Range
        {
            enum RANGE {OPEN, CLOSE} range;
            bool IsOpen() const
            {
                return (range == OPEN);
            }
            bool IsClose() const
            {
                return (range == CLOSE);
            }
            T min;
            T max;
        };
    } // namespace pluralTheorem
    namespace beta_mathFuncs /// Version: 0.5
    {
        auto Pow(auto x, auto exp)
        {
              return x * Pow(x, exp - 1);
        }
        auto Root(auto x, auto n)
        {
              return Pow(x, 1 / n);
		}
        auto Abs(auto x = 0)
        {
              return Root(Pow(x, 2), 2);
        }
        int Signum(auto x = 0)
        {
             if(x != 0) return x / Abs(x);
             else return 0;
        }

        auto SquareArea(auto a = 0)
        {
              return a * a;
        }

        auto RectangleArea(auto a = 0, auto b = a) 
        {
            return a * b;
        }

        auto TriangleArea(auto a = 0, auto h = 0)
        {
            return (a * h) / 2; 
        }

        auto ParallelogramArea(auto a = 0, auto h = Root(Pow(a, 2) - Pow(a/2, 2)))
        {
            return RectangleArea(a, h);
        }

        auto DefaultSafeDiv(auto a, auto b)
        {
            return (b != 0) ? ((a / b) : DEFAULT_ERR);
        }

        auto SafeDiv(auto a, auto b, auto  err_arg)
        {
            return (b != 0) ? ((a / b) : ERR(err_arg)));
        }
        
        auto InterpolateFunc(auto y0, auto y1, auto x0, auto x, auto x1) // "Lerp"; Returns y
        {
            return (y0 + ( ( (y1 - y0) / (x1 - x0) ) * (x - x0) ) );
        }
        
        auto Clamp(auto val, Range range);
        {
            if(range.IsOpen()
            {
                if((range.min < val) && (val < range.max)) return val;
                else if(range.min >= val) { val = range.min; return val; }
                else { val = range.max; return val; }
			}
            else if(range.IsClose())
            {
                if((range.min <= val) && (val <= range.max)) return val;
                else if(range.min > val) { val = range.min; return val; }
                else { val = range.max; return val; }
            }
        }
    } // namespace mathFuncs
    
  } // namespace Math
  
  //=======================================================================================
  
  // Physics
  namespace alpha_Physics /// Version: 0.2
  {
    namespace proto_quantMechs /// Version: 0.1.5
    {
      // Quantum Constants
      static unsigned int VoidQuantState() const // |0>
      {
        return 0;
      }
      // Quantum Objects
      struct quantObj
      {
        unsigned int m; // mass
        unsigned int QuantState; // quantum state, |n>
        unsigned int Creation(quantObj.QuantState)
          return ++quantObj.QuantState; /// If you want to change quantum state of void to |2>, you must |0> * (creation operator^2) (in this func: Creation(Creation(VoidQuantState));
        
        unsigned int Annihilation(quantObj.QuantState)
          return --quantObj.QuantState;
        
        //--------------------------------------------------------------------------------
        // Operators
        
        std::ostream& operator<<(std::ostream& quant, quantObj.QuantState) // returns "|n>"
          return quant << '|' << quantObj.QuantState << '>';
      }
    } // namespace quantObj
  } // namespace Physics
#endif
