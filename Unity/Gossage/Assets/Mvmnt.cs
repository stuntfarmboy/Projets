using UnityEngine;
using System.Collections;

public class Mvmnt : MonoBehaviour {
	public float amount = 200f;
	void Update () {
		GetComponent<Rigidbody>().AddTorque(Vector3.back * Input.GetAxis("Horizontal") * amount * Time.deltaTime);
		GetComponent<Rigidbody>().AddTorque(Vector3.right * Input.GetAxis("Vertical") * amount * Time.deltaTime);
	}
}
