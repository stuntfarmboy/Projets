using UnityEngine;
using System.Collections;

public class Follow : MonoBehaviour {
	public Transform target;
	public Vector3 offset;
	void Update () {
		Vector3 pos;
		pos.x = target.position.x + offset.x;
		pos.y = target.position.y + offset.y;
		pos.z = target.position.z + offset.z;
		transform.position = pos; 
		transform.LookAt(target.position);
	}
}
