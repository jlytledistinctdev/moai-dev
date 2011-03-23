// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef VEC3D_H
#define	VEC3D_H

template < typename TYPE > class tVec2;

//================================================================//
// USMetaVec3D
//================================================================//
/**	@brief Template class for two-dimensional vector math.
	@tparam TYPE Type of elements.  Must implement all built-in math operators.
	@ingroup MathLib
*/
template < typename TYPE >
class USMetaVec3D {
public:

	TYPE	mX;
	TYPE	mY;
	TYPE	mZ;

	//----------------------------------------------------------------//
	// V = V + vec
	void Add ( const USMetaVec3D < TYPE >& vec ) {
		mX = mX + vec.mX;
		mY = mY + vec.mY;
		mZ = mZ + vec.mZ;
	}

	//----------------------------------------------------------------//
	// V += vec * scale
	void Add ( const USMetaVec3D < TYPE >& vec, TYPE scale ) {
		mX = mX + ( vec.mX * scale );
		mY = mY + ( vec.mY * scale );
		mZ = mZ + ( vec.mZ * scale );
	}

	//----------------------------------------------------------------//
	// Clamps in positive and negative
	void Clamp ( const USMetaVec3D < TYPE >& clamp ) {
		if ( mX > clamp.mX ) mX = clamp.mX;
		else if ( mX < -clamp.mX ) mX = -clamp.mX;
		if ( mY > clamp.mY ) mY = clamp.mY;
		else if ( mY < -clamp.mY ) mY = -clamp.mY;
		if ( mZ > clamp.mZ ) mZ = clamp.mZ;
		else if ( mZ < -clamp.mZ ) mZ = -clamp.mZ;
	}

	//----------------------------------------------------------------//
	// Is V within res of vec?
	bool Compare ( const USMetaVec3D < TYPE >& vec, TYPE res ) {

		if ((( mX <= ( vec.mX + res )) && ( mX >= ( vec.mX - res ))) &&
			(( mY <= ( vec.mY + res )) && ( mY >= ( vec.mY - res ))) &&
			(( mZ <= ( vec.mZ + res )) && ( mZ >= ( vec.mZ - res )))) return true;

		return false;
	}

	//----------------------------------------------------------------//
	// V = V x vec
	void Cross ( const USMetaVec3D < TYPE >& vec ) {
		float tx;
		float ty;

		tx	= ( mY * vec.mZ ) - ( mZ * vec.mY );
		ty	= ( mZ * vec.mX ) - ( mX * vec.mZ );
		mZ	= ( mX * vec.mY ) - ( mY * vec.mX );
		mY = ty;
		mX = tx;
	}

	//----------------------------------------------------------------//
	// V = v0 x v1
	void Cross ( const USMetaVec3D < TYPE >& v0, const USMetaVec3D < TYPE >& v1 ) {
		float tx;
		float ty;

		tx	= ( v0.mY * v1.mZ ) - ( v0.mZ * v1.mY );
		ty	= ( v0.mZ * v1.mX ) - ( v0.mX * v1.mZ );
		mZ	= ( v0.mX * v1.mY ) - ( v0.mY * v1.mX );
		mY = ty;
		mX = tx;
	}

	//----------------------------------------------------------------//
	// |V| -= damp
	void Dampen ( const USMetaVec3D < TYPE >& damp ) {
		if ( mX > ( TYPE )0 ) {
			mX -= damp.mX;
			if ( mX < ( TYPE )0 ) mX = ( TYPE )0;
		}
		else if ( mX < ( TYPE )0 ) {
			mX += damp.mX;
			if ( mX > ( TYPE )0 ) mX = ( TYPE )0;
		}

		if ( mY > ( TYPE )0 ) {
			mY -= damp.mY;
			if ( mY < ( TYPE )0 ) mY = ( TYPE )0;
		}
		else if ( mY < ( TYPE )0 ) {
			mY += damp.mY;
			if ( mY > ( TYPE )0 ) mY = ( TYPE )0;
		}

		if ( mZ > ( TYPE )0 ) {
			mZ -= damp.mZ;
			if ( mZ < ( TYPE )0 ) mZ = ( TYPE )0;
		}
		else if ( mZ < ( TYPE )0 ) {
			mZ += damp.mZ;
			if ( mZ > ( TYPE )0 ) mZ = ( TYPE )0;
		}
	}

	//----------------------------------------------------------------//
	// V . vec
	float Dot ( const USMetaVec3D < TYPE >& vec ) {
		return ( mX * vec.mX ) + ( mY * vec.mY ) + ( mZ * vec.mZ );
	}

	//----------------------------------------------------------------//
	void Init ( TYPE x, TYPE y, TYPE z ) {
		mX = x;
		mY = y;
		mZ = z;
	}

	//----------------------------------------------------------------//
	template < typename PARAM_TYPE >
	void Init ( tVec2 < PARAM_TYPE >& point ) {
		mX = ( TYPE )point.mX;
		mY = ( TYPE )point.mY;
		mZ = 0;
	}

	//----------------------------------------------------------------//
	template < typename PARAM_TYPE >
	void Init ( USMetaVec3D < PARAM_TYPE >& vec ) {
		mX = ( TYPE )vec.mX;
		mY = ( TYPE )vec.mY;
		mZ = ( TYPE )vec.mZ;
	}

	//----------------------------------------------------------------//
	// V = -V
	void Invert () {
		mX = -mX;
		mY = -mY;
		mZ = -mZ;
	}

	//----------------------------------------------------------------//
	// |V|
	float Length () {
		return sqrtf (( mX * mX ) + ( mY * mY ) + ( mZ * mZ ));
	}

	//----------------------------------------------------------------//
	void Lerp ( USMetaVec3D& vec, TYPE time ) {

		this->mX = this->mX + (( vec.mX - this->mX ) * time );
		this->mY = this->mY + (( vec.mY - this->mY ) * time );
		this->mZ = this->mZ + (( vec.mZ - this->mZ ) * time );
	}

	//----------------------------------------------------------------//
	// V *= vec
	void Multiply ( const USMetaVec3D < TYPE >& vec ) {
		mX = mX * vec.mX;
		mY = mY * vec.mY;
		mZ = mZ * vec.mZ;
	}

	//----------------------------------------------------------------//
	TYPE Norm () {

		TYPE length;
		
		length = this->Length ();

		this->mX = this->mX / length;
		this->mY = this->mY / length;
		this->mZ = this->mZ / length;

		return length;
	}

	//----------------------------------------------------------------//
	TYPE NormSafe () {

		TYPE length;
		
		length = this->Length ();

		if ( length != 0 ) {
			this->mX = this->mX / length;
			this->mY = this->mY / length;
			this->mZ = this->mZ / length;
		}

		return length;
	}

	//----------------------------------------------------------------//
	// V += vec * d
	void Offset ( const USMetaVec3D < TYPE >& vec, TYPE d ) {
		mX += vec.mX * d;
		mY += vec.mY * d;
		mZ += vec.mZ * d;
	}

	//----------------------------------------------------------------//
	void Project ( USMetaVec3D < TYPE >& norm ) {

		TYPE dot;
		
		dot = this->Dot ( norm );

		this->mX -= norm.mX * dot;
		this->mY -= norm.mY * dot;
		this->mZ -= norm.mZ * dot;
	}

	//----------------------------------------------------------------//
	void Project ( USMetaVec3D < TYPE >& norm, USMetaVec3D < TYPE >& axis ) {

		TYPE project = norm.Dot ( axis ) / Dot ( norm );

		this->mX -= axis.mX * project;
		this->mY -= axis.mY * project;
		this->mZ -= axis.mZ * project;
	}

	//----------------------------------------------------------------//
	void Quantize ( TYPE decimalPlace ) {

		TYPE reciprocal = 1 / decimalPlace;
		
		this->mX = (( s32 )this->mX * reciprocal ) * decimalPlace;
		this->mY = (( s32 )this->mY * reciprocal ) * decimalPlace;
		this->mZ = (( s32 )this->mZ * reciprocal ) * decimalPlace;
	}

	//----------------------------------------------------------------//
	void Reflect ( USMetaVec3D < TYPE >& norm ) {
		TYPE dot;
		
		dot = 2.0f * this->Dot ( norm );

		this->mX -= norm.mX * dot;
		this->mY -= norm.mY * dot;
		this->mZ -= norm.mZ * dot;
	}

	//----------------------------------------------------------------//
	void Res ( TYPE res ) {

		this->mX = ((( s32 )( this->mX / res )) * res );
		this->mY = ((( s32 )( this->mY / res )) * res );
		this->mZ = ((( s32 )( this->mZ / res )) * res );
	}

	//----------------------------------------------------------------//
	// Rotates about the Z axis (implicit by the orthogonal normals provided)
	void RotateInBasis	( USMetaVec3D < TYPE >& xAxis, USMetaVec3D < TYPE >& yAxis, TYPE theta ) {

		// Do the trig for the angle
		TYPE sinTheta = Sin ( theta );
		TYPE cosTheta = Cos ( theta );

		// Yank out the vector components in terms of the local axes
		TYPE x = Dot ( xAxis );
		TYPE y = Dot ( yAxis );

		// Move the vector back to the origin ( do it this way to preserve the z component )
		this->mX -= ( x * xAxis.mX ) - ( y * yAxis.mX );
		this->mY -= ( x * xAxis.mY ) - ( y * yAxis.mY );
		this->mZ -= ( x * xAxis.mZ ) - ( y * yAxis.mZ );

		// Figure the new components
		TYPE xP = ( x * cosTheta ) - ( y * sinTheta );
		TYPE yP = ( y * cosTheta ) + ( x * sinTheta );

		// Move the vector to its new rotated position
		this->mX += ( xP * xAxis.mX ) + ( yP * yAxis.mX );
		this->mY += ( xP * xAxis.mY ) + ( yP * yAxis.mY );
		this->mZ += ( xP * xAxis.mZ ) + ( yP * yAxis.mZ );
	}

	//----------------------------------------------------------------//
	// V *= scale
	void Scale ( TYPE scale ) {
		mX *= scale;
		mY *= scale;
		mZ *= scale;
	}

	//----------------------------------------------------------------//
	TYPE SetLength ( TYPE length ) {

		TYPE scale;
		scale = this->Length () / length;

		this->mX = this->mX / scale;
		this->mY = this->mY / scale;
		this->mZ = this->mZ / scale;

		return length;
	}

	//----------------------------------------------------------------//
	// V = V - vec
	void Sub ( const USMetaVec3D < TYPE >& vec ) {
		mX -= vec.mX;
		mY -= vec.mY;
		mZ -= vec.mZ;
	}

	//----------------------------------------------------------------//
	// V -= vec * scale
	void Sub ( const USMetaVec3D < TYPE >& vec, TYPE scale ) {
		mX = mX - ( vec.mX * scale );
		mY = mY - ( vec.mY * scale );
		mZ = mZ - ( vec.mZ * scale );
	}

	//----------------------------------------------------------------//
	USMetaVec3D () {
	}

	//----------------------------------------------------------------//
	USMetaVec3D ( TYPE x, TYPE y, TYPE z ) :
		mX ( x ),
		mY ( y ),
		mZ ( z ) {
	}

	//----------------------------------------------------------------//
	~USMetaVec3D () {
	}
};

//================================================================//
// USIntVec3D
//================================================================//
/**	@brief 3D integer vector.
	@ingroup MathLib
*/
class USIntVec3D :
	public USMetaVec3D < int > {
public:

	//----------------------------------------------------------------//
	/**	@brief Constructor.
	*/	
	USIntVec3D () {
	}

	//----------------------------------------------------------------//
	/**	@brief Constructor.
	*/	
	USIntVec3D ( int x, int y, int z ) :
		USMetaVec3D < int > ( x, y, z ) {
	}
};

//================================================================//
// USVec3D
//================================================================//
/**	@brief 3D float vector.
	@ingroup MathLib
*/
class USVec3D :
	public USMetaVec3D < float > {
public:

	//----------------------------------------------------------------//
	/**	@brief Constructor.
	*/	
	USVec3D () {
	}

	//----------------------------------------------------------------//
	/**	@brief Constructor.
	*/	
	USVec3D ( float x, float y, float z ) :
		USMetaVec3D < float > ( x, y, z ) {
	}
};

//================================================================//
// USVec3D64
//================================================================//
/**	@brief 3D double vector.
	@ingroup MathLib
*/
class USVec3D64 :
	public USMetaVec3D < double > {
public:

	//----------------------------------------------------------------//
	/**	@brief Constructor.
	*/	
	USVec3D64 () {
	}

	//----------------------------------------------------------------//
	/**	@brief Constructor.
	*/	
	USVec3D64 ( double x, double y, double z ) :
		USMetaVec3D < double > ( x, y, z ) {
	}
};


#endif